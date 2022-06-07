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

static constexpr double pi = M_PI;

static constexpr double epsilon = 1e-6;

constexpr double minDouble = std::numeric_limits<double>::min();
constexpr double maxDouble = std::numeric_limits<double>::max();

static inline const Vec3 nullRgb(minDouble, minDouble, minDouble);

static inline const Vec3 zerov(0, 0, 0);
static inline const Vec3 up(0, 1, 0);

constexpr inline double toRad(double deg) {
    return deg * pi / 180;
}

inline bool isZero(double d) {
	return std::fabs(d) < epsilon;
}

inline double calcPositiveMin(double x, double y) {
	bool xNegative = x < 0.0;
	bool yNegative = y < 0.0;
	if (xNegative && yNegative) return -1;
	if (xNegative) return y;
	if (yNegative) return x;
	return std::min(x, y);
}

inline Vec3 reflect(const Vec3& d, const Vec3& n) {
	return d - 2 * (d.dot(n)) * n;
}

inline Vec3 refract(const Vec3& i, const Vec3& n, double refracRatio) {
	double cosi = std::clamp(-1.0, 1.0, i.dot(n));
	Vec3 normal;
	double eta;
	if (cosi < 0.0) {
		cosi = -cosi;
		normal = n;
		eta = 1 / refracRatio;
	} else {
		normal = -n;
		eta = refracRatio;
	}
	double discr = 1 - eta * eta * (1 - cosi * cosi);
	return (discr < 0.0) ? zerov : eta * i + (eta * cosi - std::sqrt(discr)) * normal;
}

#endif //COURSE_PROJECT_MATH_HPP
