#ifndef COURSE_PROJECT_MATH_HPP
#define COURSE_PROJECT_MATH_HPP

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

#include <cmath>

using Transform = Eigen::Transform<double, 3, Eigen::TransformTraits::Affine>;

using Vec3 = Eigen::Vector3d;

using Mat3 = Eigen::Matrix3d;
using Mat4 = Eigen::Matrix4d;

using IndexTriple = Eigen::Vector3i;

using AngleAxis = Eigen::AngleAxis<double>;

using Eigen::Scaling;

const Vec3 up(0, 1, 0);

constexpr inline double toRad(double deg) {
    return deg * M_PI / 180;
}

#endif //COURSE_PROJECT_MATH_HPP
