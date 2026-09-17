#pragma once

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "async/parallel_for.h"
#include "async/thread_pool.h"
#include "initializer/interactive_search/common/common.h"
#include "initializer/interactive_search/common/interactive_a_star_constant.h"
#include "math/frenet_frame.h"
#include "math/vec.h"

namespace pnc_x {
namespace planning {

class GridMap final {
 public:
    GridMap();
    GridMap(int row_num, int column_num, double sizeX, double sizeY);
    GridMap(const GridMap &other)
        : grid_map_(new GridStatus[other.row_size_ * other.column_size_]),
          rotation_matrix_world2grid_(other.rotation_matrix_world2grid_),
          translation_vec_world2grid_(other.translation_vec_world2grid_),
          cSizeX_(other.cSizeX_),
          cSizeY_(other.cSizeY_),
          delta_yaw_(other.delta_yaw_),
          row_size_(other.row_size_),
          column_size_(other.column_size_),
          obs_id_in_map_(other.obs_id_in_map_) {
        std::copy(other.grid_map_,
                  other.grid_map_ + (other.row_size_ * other.column_size_),
                  grid_map_);
    }

    ~GridMap() {
        if (grid_map_ != nullptr) {
            delete[] grid_map_;
        }
        grid_map_ = nullptr;
    };

    GridMap &operator=(const GridMap &other);

    void InitGridMap(int row_num, int column_num, double sizeX, double sizeY);

    void TransformCoordinates(const double x_translation,
                              const double y_translation,
                              const double yaw);

    void SetUpGridMap(const std::vector<std::vector<Vec2d>> &obstacles);

    void ObstainMinXYforObs(const std::vector<Vec2d> &obs_vertices,
                            int &Xmin,
                            int &Xmax,
                            int &Ymin,
                            int &Ymax);

    void FillBorder(const std::vector<Vec2d> &obs_vertices,
                    std::vector<GridStatus> &current_grid_map,
                    int Xmin,
                    int Xmax,
                    int Ymin,
                    int Ymax);
    void FillShape(std::vector<GridStatus> &current_grid_map,
                   int Xmin,
                   int Xmax,
                   int Ymin,
                   int Ymax);

    bool CheckIfPointInSearchBoundary(double x, double y) const;

    void GetGridMap(std::vector<std::vector<GridStatus>> &grid_map) const;

    bool GetValue(int i, int j, GridStatus &value);

    int GetYSize() const { return row_size_; };

    int GetXSize() const { return column_size_; }

    double GetCellSizeX() const { return cSizeX_; }

    double GetCellSizeY() const { return cSizeY_; }

    std::pair<Vec2d, Vec2d> GetRotationMatrix() const {
        return rotation_matrix_world2grid_;
    }

    Vec2d GetTranslationVec() const { return translation_vec_world2grid_; }

    void SetStatus(int x, int y, GridStatus status);

    std::vector<int> MapPos2GridIndex(double x, double y) const;

    bool PointInGridMap(int x_index, int y_index) const;

    bool CheckXYVaild(const int Xmin,
                      const int Ymin,
                      const int Xmax,
                      const int Ymax,
                      const int X,
                      const int Y,
                      const std::vector<GridStatus> &current_grid_map);

    void SafeSetObs(const int Xmin,
                    const int Ymin,
                    const int Xmax,
                    const int Ymax,
                    const int X,
                    const int Y,
                    std::vector<GridStatus> &current_grid_map);

 private:
    int sign(double x) {
        if (x >= 0.0) {
            return 1;
        } else {
            return -1;
        }
    }

    GridStatus *grid_map_ = nullptr;
    std::pair<Vec2d, Vec2d> rotation_matrix_world2grid_;
    Vec2d translation_vec_world2grid_;
    double cSizeX_;
    double cSizeY_;
    double delta_yaw_;
    int row_size_;
    int column_size_;
    std::map<std::pair<int, int>, int> obs_id_in_map_;
};

class GridMapManager {
 public:
    void InitOccMap(const GridMapInformation &map_info, GridMap &gridmap) const;

    void OccMapDebug(GridMap &gridmap, const std::string &path);

    void GetXYMinMaxInGridMap(int grid_x,
                              int grid_y,
                              int &x_max_in_grid,
                              int &y_max_in_grid,
                              int &x_min_in_grid,
                              int &y_min_in_grid);

    template <typename T>
    double minBoundingAngle(const std::vector<T> &points);

    void GetGridMapBiasAndLength(const LeftRightXYBoundPoints &left_right_bound,
                                 double x_cell,
                                 double y_cell,
                                 GridMapInformation &bias);

    void InterpolationBasedTwoPoint(const std::pair<int, int> &point_start,
                                    const std::pair<int, int> &point_end,
                                    const double distance,
                                    std::vector<Point2D> &points) const;
};

}  // namespace planning
}  // namespace pnc_x
