#include "grid_map.h"
#include "async/thread_pool.h"

#include <climits>
#include <vector>

#define DEBUG false

namespace pnc_x {
namespace planning {

GridMap::GridMap() = default;

GridMap::GridMap(int row_num, int column_num, double sizeX, double sizeY) {
    grid_map_ =
        new GridStatus[static_cast<unsigned long>(row_num * column_num)]();
    std::fill(grid_map_, grid_map_ + (row_num * column_num), GridStatus::kFree);
    row_size_ = row_num;
    column_size_ = column_num;
    cSizeX_ = sizeX;
    cSizeY_ = sizeY;
    delta_yaw_ = 0.0;
    obs_id_in_map_.clear();
}

void GridMap::InitGridMap(int row_num,
                          int column_num,
                          double sizeX,
                          double sizeY) {
    grid_map_ =
        new GridStatus[static_cast<unsigned long>(row_num * column_num)]();
    std::fill(grid_map_, grid_map_ + (row_num * column_num), GridStatus::kFree);
    row_size_ = row_num;
    column_size_ = column_num;
    cSizeX_ = sizeX;
    cSizeY_ = sizeY;
    delta_yaw_ = 0.0;
    obs_id_in_map_.clear();
}

bool GridMap::GetValue(int i, int j, GridStatus &value) {
    if ((row_size_ == 0) || (column_size_ == 0)) {
        return false;
    }
    if ((i >= 0) && (i < row_size_) && (j >= 0) && (j < column_size_)) {
        value = grid_map_[(i * column_size_) + j];
        return true;
    }
    return false;
}

void GridMap::TransformCoordinates(const double x_translation,
                                   const double y_translation,
                                   const double yaw) {
    delta_yaw_ = yaw;
    rotation_matrix_world2grid_.first = Vec2d(
        pnc_x::fast_math::Cos(delta_yaw_), -pnc_x::fast_math::Sin(delta_yaw_));
    rotation_matrix_world2grid_.second = Vec2d(
        pnc_x::fast_math::Sin(delta_yaw_), pnc_x::fast_math::Cos(delta_yaw_));
    translation_vec_world2grid_ = {x_translation, y_translation};
}

void GridMap::SetUpGridMap(const std::vector<std::vector<Vec2d>> &obstacles) {
    int Xmin = 0;
    int Xmax = 0;
    int Ymin = 0;
    int Ymax = 0;
    std::vector<GridStatus> current_grid_map;
    for (int obs_index = 0; obs_index < obstacles.size(); ++obs_index) {
        const auto &obs_vertices = obstacles[static_cast<size_t>(obs_index)];
        Xmax = INT_MIN;
        Xmin = INT_MAX;
        Ymax = INT_MIN;
        Ymin = INT_MAX;
        ObstainMinXYforObs(obs_vertices, Xmin, Xmax, Ymin, Ymax);
        current_grid_map.clear();
        for (int i = 0; i <= Ymax - Ymin; ++i) {
            for (int j = 0; j <= Xmax - Xmin; ++j) {
                current_grid_map.push_back(GridStatus::kFree);
            }
        }

        FillBorder(obs_vertices, current_grid_map, Xmin, Xmax, Ymin, Ymax);
        FillShape(current_grid_map, Xmin, Xmax, Ymin, Ymax);

        for (int i = 0; i <= Ymax - Ymin; ++i) {
            for (int j = 0; j <= Xmax - Xmin; ++j) {
                if (current_grid_map[(i * (Xmax - Xmin + 1)) + j] ==
                    GridStatus::kOccupied) {
                    if (((i + Ymin) >= 0) && ((j + Xmin) >= 0) &&
                        ((i + Ymin) < row_size_) &&
                        ((j + Xmin) < column_size_)) {
                        grid_map_[((i + Ymin) * column_size_) + j + Xmin] =
                            GridStatus::kOccupied;
                        obs_id_in_map_[{i + Ymin, j + Xmin}] = obs_index;
                    }
                }
            }
        }
    }
}

void GridMap::ObstainMinXYforObs(const std::vector<Vec2d> &obs_vertices,
                                 int &Xmin,
                                 int &Xmax,
                                 int &Ymin,
                                 int &Ymax) {
    int X = 0;
    int Y = 0;
    int x_max_tmp;
    int y_max_tmp;
    int x_min_tmp;
    int y_min_tmp;
    for (int k = 0; k < obs_vertices.size(); ++k) {
        Vec2d xy_grid_index((obs_vertices[static_cast<size_t>(k)] + translation_vec_world2grid_)
                                .InnerProd(rotation_matrix_world2grid_.first),
                            (obs_vertices[static_cast<size_t>(k)] + translation_vec_world2grid_)
                                .InnerProd(rotation_matrix_world2grid_.second));

        xy_grid_index = {xy_grid_index.x() / cSizeX_,
                         xy_grid_index.y() / cSizeY_};
        X = (int)(xy_grid_index.x() + kEpsilon);
        Y = (int)(xy_grid_index.y() + kEpsilon);

        if (X < Xmin) {
            Xmin = X;
        }
        if (X > Xmax) {
            Xmax = X;
        }
        if (Y < Ymin) {
            Ymin = Y;
        }
        if (Y > Ymax) {
            Ymax = Y;
        }
    }
}

void GridMap::FillBorder(const std::vector<Vec2d> &obs_vertices,
                         std::vector<GridStatus> &current_grid_map,
                         int Xmin,
                         int Xmax,
                         int Ymin,
                         int Ymax) {
    int num_vertices = obs_vertices.size();

    double tDeltaX;
    double tDeltaY;

    int stepX;
    int stepY;

    double tMaxX;
    double tMaxY;
    for (int k = 0; k < num_vertices; ++k) {
        Vec2d start_tmp((obs_vertices[static_cast<size_t>(k)] + translation_vec_world2grid_)
                            .InnerProd(rotation_matrix_world2grid_.first),
                        (obs_vertices[static_cast<size_t>(k)] + translation_vec_world2grid_)
                            .InnerProd(rotation_matrix_world2grid_.second));

        Vec2d start = {start_tmp.x() / cSizeX_, start_tmp.y() / cSizeY_};

        Vec2d end_tmp(
            (obs_vertices[static_cast<size_t>((k + 1) % num_vertices)] + translation_vec_world2grid_)
                .InnerProd(rotation_matrix_world2grid_.first),
            (obs_vertices[static_cast<size_t>((k + 1) % num_vertices)] + translation_vec_world2grid_)
                .InnerProd(rotation_matrix_world2grid_.second));

        Vec2d end = {end_tmp.x() / cSizeX_, end_tmp.y() / cSizeY_};

        int X = start.x();
        int Y = start.y();
        current_grid_map[static_cast<size_t>(((Y - Ymin) * (Xmax - Xmin + 1)) + (X - Xmin))] =
            GridStatus::kOccupied;

        Vec2d delta_vec(end.x() - start.x(), end.y() - start.y());

        stepX = sign(delta_vec.x());
        stepY = sign(delta_vec.y());

        if (delta_vec.x() != 0.0)
            tDeltaX = 1.F / std::abs(delta_vec.x());
        else {
            tDeltaX = 1000.0;
        }

        if (delta_vec.y() != 0.0) {
            tDeltaY = 1.F / std::abs(delta_vec.y());
        } else {
            tDeltaY = 1000.0;
        }

        if (stepX > 0) {
            tMaxX = tDeltaX * (1 - (start.x() - (long)(start.x() + kEpsilon)));
        } else {
            tMaxX = tDeltaX * (start.x() - (long)(start.x() + kEpsilon));
        }
        if (stepY > 0) {
            tMaxY = tDeltaY * (1 - (start.y() - (long)(start.y() + kEpsilon)));
        } else {
            tMaxY = tDeltaY * (start.y() - (long)(start.y() + kEpsilon));
        }
        while (((int)(end.x() + kEpsilon) != X) ||
               ((int)(end.y() + kEpsilon) != Y)) {
            if ((tMaxX < tMaxY) &&
                (std::abs(X + stepX - (int)(end.x() + kEpsilon)) <
                 std::abs(X - (int)(end.x() + kEpsilon)))) {
                tMaxX = tMaxX + tDeltaX;
                X = X + stepX;
                current_grid_map[static_cast<size_t>(((Y - Ymin) * (Xmax - Xmin + 1)) +
                                 (X - Xmin))] = GridStatus::kOccupied;
            } else if ((tMaxY < tMaxX) &&
                       (std::abs(Y + stepY - (int)(end.y() + kEpsilon)) <
                        std::abs(Y - (int)(end.y() + kEpsilon)))) {
                tMaxY = tMaxY + tDeltaY;
                Y = Y + stepY;
                current_grid_map[static_cast<size_t>(
                    ((Y - Ymin) * (Xmax - Xmin + 1)) + (X - Xmin))] =
                    GridStatus::kOccupied;
            } else if (2 >= (std::abs(X - (int)(end.x() + kEpsilon)) +
                             std::abs(Y - (int)(end.y() + kEpsilon)))) {
                if (std::abs(X - (int)(end.x() + kEpsilon)) >
                    std::abs(Y - (int)(end.y() + kEpsilon))) {
                    X = X + stepX;
                    current_grid_map[static_cast<size_t>(((Y - Ymin) * (Xmax - Xmin + 1)) +
                                     (X - Xmin))] = GridStatus::kOccupied;
                } else {
                    Y = Y + stepY;
                    current_grid_map[static_cast<size_t>(((Y - Ymin) * (Xmax - Xmin + 1)) +
                                     (X - Xmin))] = GridStatus::kOccupied;
                }
            } else {
                break;
            }
        }
    }
}

void GridMap::FillShape(std::vector<GridStatus> &current_grid_map,
                        int Xmin,
                        int Xmax,
                        int Ymin,
                        int Ymax) {
    bool inside = false;
    int hcross1 = 0;
    int hcross2 = 0;
    for (int i = Ymin; i <= Ymax; ++i) {
        inside = false;

        for (int k = Xmin; k <= Xmax; ++k) {
            if ((current_grid_map[((i - Ymin) * (Xmax - Xmin + 1)) +
                                  (k - Xmin)] == GridStatus::kOccupied) &&
                !inside) {
                hcross1 = k;
                inside = true;
            }
            if ((current_grid_map[((i - Ymin) * (Xmax - Xmin + 1)) +
                                  (k - Xmin)] == GridStatus::kOccupied) &&
                inside) {
                hcross2 = k;
            }
        }

        for (int j = Xmin; j <= Xmax; ++j) {
            if ((j > hcross1) && (j < hcross2) && inside) {
                current_grid_map[static_cast<size_t>(((i - Ymin) * (Xmax - Xmin + 1)) +
                                 (j - Xmin))] = GridStatus::kOccupied;
            }
        }
    }
}

void GridMap::SetStatus(int x, int y, GridStatus status) {
    if ((column_size_ == 0) || (row_size_ == 0)) {
        return;
    }
    if ((y < row_size_) && (y >= 0) && (x < column_size_) && (x >= 0)) {
        grid_map_[(y * column_size_) + x] = status;
    }
}

bool GridMap::CheckXYVaild(const int Xmin,
                           const int Ymin,
                           const int Xmax,
                           const int Ymax,
                           const int X,
                           const int Y,
                           const std::vector<GridStatus> &current_grid_map) {
    if (((Y - Ymin) * (Xmax - Xmin + 1)) + (X - Xmin) >=
        current_grid_map.size()) {
        return false;
    }
    return true;
}

void GridMap::SafeSetObs(const int Xmin,
                         const int Ymin,
                         const int Xmax,
                         const int Ymax,
                         const int X,
                         const int Y,
                         std::vector<GridStatus> &current_grid_map) {
    if (!CheckXYVaild(Xmin, Ymin, Xmax, Ymax, X, Y, current_grid_map)) {
        return;
    }
    current_grid_map[static_cast<size_t>(((Y - Ymin) * (Xmax - Xmin + 1)) + (X - Xmin))] =
        GridStatus::kOccupied;
}

bool GridMap::CheckIfPointInSearchBoundary(double x, double y) const {
    const auto &grid_index = MapPos2GridIndex(x, y);
    int X = grid_index[static_cast<size_t>(kXIndex)];
    int Y = grid_index[static_cast<size_t>(kYIndex)];

    bool point_in_gridmap_area = PointInGridMap(X, Y);

    if (!point_in_gridmap_area ||
        (grid_map_[((Y * column_size_) + X)] != GridStatus::kFree)) {
        return false;
    }
    return true;
}

bool GridMap::PointInGridMap(int x_index, int y_index) const {
    return (x_index >= 0) && (x_index < column_size_) && (y_index >= 0) &&
           (y_index < row_size_);
}

std::vector<int> GridMap::MapPos2GridIndex(double x, double y) const {
    Vec2d pos_in_world{x, y};
    Vec2d xy_grid((pos_in_world + translation_vec_world2grid_)
                      .InnerProd(rotation_matrix_world2grid_.first),
                  (pos_in_world + translation_vec_world2grid_)
                      .InnerProd(rotation_matrix_world2grid_.second));
    Vec2d xy_grid_index = {xy_grid.x() / cSizeX_, xy_grid.y() / cSizeY_};

    int X = static_cast<int>(xy_grid_index.x() + kEpsilon);
    int Y = static_cast<int>(xy_grid_index.y() + kEpsilon);

    return {X, Y};
}

void GridMap::GetGridMap(std::vector<std::vector<GridStatus>> &grid_map) const {
    grid_map.clear();
    for (int i = 0; i < row_size_; ++i) {
        std::vector<GridStatus> tmp;
        tmp.reserve(static_cast<size_t>(column_size_));
        for (int j = 0; j < column_size_; ++j) {
            tmp.push_back(grid_map_[(i * column_size_) + j]);
        }
        grid_map.emplace_back(std::move(tmp));
    }
}

template <typename T>
double GridMapManager::minBoundingAngle(const std::vector<T> &points) {
    const int n = points.size();
    if (n < 2) {
        return 0.0;
    }

    double min_angle = 2.0 * M_PI;
    int index = 0;

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        int k = (i + 2) % n;

        double dx1 = points[j].x - points[i].x;
        double dy1 = points[j].y - points[i].y;
        double dx2 = points[k].x - points[j].x;
        double dy2 = points[k].y - points[j].y;

        double dot_product = (dx1 * dx2) + (dy1 * dy2);
        double cross_product = (dx1 * dy2) - (dy1 * dx2);
        double angle = atan2(cross_product, dot_product);

        if (angle < 0) {
            angle += 2.0 * M_PI;
        }
        if (angle < min_angle) {
            min_angle = angle;
            index = j;
        }
    }

    double dx1 = points[index].x - points[index - 1].x;
    double dy1 = points[index].y - points[index - 1].y;
    double theta = atan2(dy1, dx1);

    return -theta + (0.5 * min_angle);
}

void GridMapManager::GetGridMapBiasAndLength(
    const LeftRightXYBoundPoints &left_right_bound,
    double x_cell,
    double y_cell,
    GridMapInformation &bias) {
    if (left_right_bound.size() != kBoundNum) {
        return;
    }
    const auto &points_left = left_right_bound[0];
    const auto &points_right = left_right_bound[1];

    int x_max_in_grid = INT_MIN;
    int x_min_in_grid = INT_MAX;
    int y_max_in_grid = INT_MIN;
    int y_min_in_grid = INT_MAX;
    bias.rotation_angle = 0.0;
    bias.x_resolution = x_cell;
    bias.y_resolution = y_cell;
    std::pair<Vec2d, Vec2d> rotation_matrix_world2grid;
    std::pair<Vec2d, Vec2d> reverse_rotation_matrix_world2grid;
    rotation_matrix_world2grid.first =
        Vec2d(pnc_x::fast_math::Cos(bias.rotation_angle),
              -pnc_x::fast_math::Sin(bias.rotation_angle));
    rotation_matrix_world2grid.second =
        Vec2d(pnc_x::fast_math::Sin(bias.rotation_angle),
              pnc_x::fast_math::Cos(bias.rotation_angle));
    reverse_rotation_matrix_world2grid.first =
        Vec2d(pnc_x::fast_math::Cos(bias.rotation_angle),
              pnc_x::fast_math::Sin(bias.rotation_angle));
    reverse_rotation_matrix_world2grid.second =
        Vec2d(-pnc_x::fast_math::Sin(bias.rotation_angle),
              pnc_x::fast_math::Cos(bias.rotation_angle));
    for (int i = 0; i < points_left.size(); ++i) {
        Vec2d v{points_left[static_cast<size_t>(i)].x, points_left[static_cast<size_t>(i)].y};
        Vec2d xy_grid_index_tmp(
            (v).InnerProd(rotation_matrix_world2grid.first),
            (v).InnerProd(rotation_matrix_world2grid.second));
        int grid_x = static_cast<int>(xy_grid_index_tmp.x() / x_cell);
        int grid_y = static_cast<int>(xy_grid_index_tmp.y() / y_cell);
        GetXYMinMaxInGridMap(grid_x, grid_y, x_max_in_grid, y_max_in_grid,
                             x_min_in_grid, y_min_in_grid);
    }
    for (int i = 0; i < points_right.size(); ++i) {
        Vec2d v{points_right[static_cast<size_t>(i)].x, points_right[static_cast<size_t>(i)].y};
        Vec2d xy_grid_index_tmp(
            (v).InnerProd(rotation_matrix_world2grid.first),
            (v).InnerProd(rotation_matrix_world2grid.second));
        int grid_x = static_cast<int>(xy_grid_index_tmp.x() / x_cell);
        int grid_y = static_cast<int>(xy_grid_index_tmp.y() / y_cell);
        GetXYMinMaxInGridMap(grid_x, grid_y, x_max_in_grid, y_max_in_grid,
                             x_min_in_grid, y_min_in_grid);
    }

    Vec2d bias_in_grid{-(static_cast<double>(x_min_in_grid) * x_cell),
                       -(static_cast<double>(y_min_in_grid) * y_cell)};
    Vec2d bias_in_world(
        (bias_in_grid).InnerProd(reverse_rotation_matrix_world2grid.first),
        (bias_in_grid).InnerProd(reverse_rotation_matrix_world2grid.second));
    bias.x_translation = bias_in_world.x();
    bias.y_translation = bias_in_world.y();
    bias.x_length =
        (static_cast<double>(x_max_in_grid) * x_cell) + bias_in_grid.x();
    bias.y_length =
        (static_cast<double>(y_max_in_grid) * y_cell) + bias_in_grid.y();
}

void GridMapManager::GetXYMinMaxInGridMap(int grid_x,
                                          int grid_y,
                                          int &x_max_in_grid,
                                          int &y_max_in_grid,
                                          int &x_min_in_grid,
                                          int &y_min_in_grid) {
    if (x_max_in_grid < grid_x) {
        x_max_in_grid = grid_x;
    }
    if (y_max_in_grid < grid_y) {
        y_max_in_grid = grid_y;
    }
    if (x_min_in_grid > grid_x) {
        x_min_in_grid = grid_x;
    }
    if (y_min_in_grid > grid_y) {
        y_min_in_grid = grid_y;
    }
}

}  // namespace planning
}  // namespace pnc_x
