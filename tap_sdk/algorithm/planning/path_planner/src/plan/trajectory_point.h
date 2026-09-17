
#pragma once

#include <algorithm>
#include <string>

#include "math/util.h"
#include "plan/second_order_trajectory_point.h"
#include "pncx_trajectory_point.pb.h"

namespace pnc_x {
namespace planning {

class TrajectoryPoint : public SecondOrderTrajectoryPoint {
 public:
    TrajectoryPoint() = default;
    explicit TrajectoryPoint(const TrajectoryPointProto &proto);
    explicit TrajectoryPoint(const ApolloTrajectoryPointProto &proto);

    static double ComputeLambda(double v, double psi);

    static double ComputeMu(double v, double a, double lambda, double chi);
    double lambda() const;
    double mu() const;

    double j() const;
    void set_j(double j);

    double psi() const;
    double chi() const;
    void set_psi(double psi);
    void set_chi(double chi);

    void FromProto(const TrajectoryPointProto &proto);
    void ToProto(TrajectoryPointProto *proto) const;

    void FromProto(const ApolloTrajectoryPointProto &proto);
    void ToProto(ApolloTrajectoryPointProto *proto) const;

    void ToProto(PoseTrajectoryPointProto *proto) const;

    std::string DebugString() const;

 private:
    static double kSpeedEps;

    double j_ = 0.0;

    double psi_ = 0.0; // dkappa
    double chi_ = 0.0; // ddkappa
};

}  // namespace planning
}  // namespace pnc_x
