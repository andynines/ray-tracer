#ifndef COURSE_PROJECT_MATH_HPP
#define COURSE_PROJECT_MATH_HPP

#include <eigen3/Eigen/Eigen>

#include <cmath>
#include <utility>

using Transform = Eigen::Transform<double, 3, Eigen::TransformTraits::Affine>;

using Vec3 = Eigen::Vector3d;
using Rgb = Vec3;

struct Material {
	Rgb color;
	double ka, ks, kd, shiny;

	Material() : ka(0), ks(0), kd(0), shiny(0) {}
};

using IndexTriple = Eigen::Vector3i;

using AngleAxis = Eigen::AngleAxis<double>;

using Eigen::Scaling;

static inline const Vec3 zero(0, 0, 0);
static inline const Vec3 up(0, 1, 0);

constexpr inline double toRad(double deg) {
    return deg * M_PI / 180;
}

#endif //COURSE_PROJECT_MATH_HPP
