

#include "maps/lane_point.h"

#include <vector>

#include "math/util.h"

namespace pnc_x {
namespace mapping {

namespace {

void GetNeighboringVertices(double fraction,
                            const std::vector<double> &cumulative_lengths,
                            const std::vector<Vec2d> &lane_vertices,
                            const std::vector<Vec2d> &lane_point_theta,
                            Vec2d *v0,
                            Vec2d *v1,
                            Vec2d *theta0,
                            Vec2d *theta1,
                            double *alpha) {
    const int num_vertices = static_cast<int>(lane_vertices.size());

    *alpha = 0.0;
    if (cumulative_lengths.empty()) {
        return;
    }
    const double s = fraction * cumulative_lengths.back();

    XCHECK_GE(s, cumulative_lengths.front());
    XCHECK_LE(s, cumulative_lengths.back());

    int i = static_cast<int>(std::upper_bound(cumulative_lengths.begin(),
                             cumulative_lengths.end(), s) -
            cumulative_lengths.begin());
    XCHECK_GT(i, 0);
    if (i == num_vertices) --i;
    const std::size_t i_prev = static_cast<std::size_t>(i) - 1U;
    *v0 = lane_vertices[i_prev];
    *v1 = lane_vertices[i];
    *theta0 = lane_point_theta[i_prev];
    *theta1 = lane_point_theta[i];
    const double s0 = cumulative_lengths[i_prev];
    const double s1 = cumulative_lengths[i];
    *alpha = (s - s0) / (s1 - s0);
    XCHECK_GE(*alpha, 0.0);
    XCHECK_LE(*alpha, 1.0);
}

}  // namespace

LanePoint::LanePoint(ElementId lane_id, double fraction)
    : lane_id_(lane_id),
      fraction_(boost::algorithm::clamp(fraction, 0.0, 1.0)) {}
LanePoint::LanePoint(const LanePointProto &proto) { FromProto(proto); }

ElementId LanePoint::lane_id() const { return lane_id_; }
double LanePoint::fraction() const { return fraction_; }
void LanePoint::set_fraction(double fraction) { fraction_ = fraction; }

bool LanePoint::Valid() const {
    return (lane_id_ != kInvalidElementId) && (fraction_ >= 0.0) &&
           (fraction_ <= 1.0);
}

std::string LanePoint::DebugString() const {
    return absl::StrFormat("{%d:%.6f}", lane_id_, fraction_);
}

bool LanePoint::operator==(const LanePoint &other) const {
    return (lane_id_ == other.lane_id_) && (fraction_ == other.fraction_);
}
bool LanePoint::operator!=(const LanePoint &other) const {
    return !(*this == other);
}

void LanePoint::ToProto(LanePointProto *proto) const {
    proto->set_lane_id(lane_id_);
    proto->set_fraction(fraction_);
}

void LanePoint::FromProto(const LanePointProto &proto) {
    lane_id_ = static_cast<pnc_x::mapping::ElementId>(proto.lane_id());
    fraction_ = boost::algorithm::clamp(proto.fraction(), 0.0, 1.0);
}

}  // namespace mapping
}  // namespace pnc_x
