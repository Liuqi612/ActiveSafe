
#pragma once

namespace ads_x {
namespace planning {
namespace math {

class Double {
 public:
    enum class CompareType : int { EQUAL = 0, LESS = -1, GREATER = 1 };
    Double() = default;
    ~Double() = default;
    static CompareType Compare(const double &a, const double &b);
    static CompareType Compare(const double &a,
                               const double &b,
                               const double &epsilon);

 private:
    static bool LessThan(const double &a,
                         const double &b,
                         const double &epsilon);
    static bool GreaterThan(const double &a,
                            const double &b,
                            const double &epsilon);

    static constexpr double epsilon_ = 1e-6;
};

}  // namespace math
}  // namespace planning
}  // namespace ads_x
