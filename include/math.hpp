#ifndef COURSE_PROJECT_MATH_HPP
#define COURSE_PROJECT_MATH_HPP

#include <eigen3/Eigen/Eigen>

#include <cmath>
#include <utility>

using Transform = Eigen::Transform<double, 3, Eigen::TransformTraits::Affine>;

using Vec3 = Eigen::Vector3d;
using Rgb = Vec3;

using IndexTriple = Eigen::Vector3<size_t>;

using AngleAxis = Eigen::AngleAxis<double>;

using Eigen::Scaling;

static constexpr double epsilon = 1e-6;

constexpr double minDouble = std::numeric_limits<double>::min();
constexpr double maxDouble = std::numeric_limits<double>::max();

static inline const Vec3 nullRgb(minDouble, minDouble, minDouble);

static inline const Vec3 zero(0, 0, 0);
static inline const Vec3 up(0, 1, 0);

constexpr inline double toRad(double deg) {
    return deg * M_PI / 180;
}

constexpr bool isZero(double d) {
	return std::fabs(d) < epsilon;
}

#endif //COURSE_PROJECT_MATH_HPP
