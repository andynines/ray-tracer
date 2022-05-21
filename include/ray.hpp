#ifndef COURSE_PROJECT_RAY_HPP
#define COURSE_PROJECT_RAY_HPP

#include "math.hpp"

struct Ray {
	Vec3 origin;
	Vec3 dir;
	Vec3 invDir;

	Ray(const Vec3& origin, const Vec3& dir) : origin(origin), dir(dir.normalized()), invDir(dir.cwiseInverse()) {}

	[[nodiscard]] inline bool hitsAabb(const Vec3& min, const Vec3& max) const {
		Vec3 tmin = (min - origin).cwiseProduct(invDir);
		Vec3 tmax = (max - origin).cwiseProduct(invDir);
		Vec3 t1{std::min(tmin[0], tmax[0]), std::min(tmin[1], tmax[1]), std::min(tmin[2], tmax[2])};
		Vec3 t2{std::max(tmin[0], tmax[0]), std::max(tmin[1], tmax[1]), std::max(tmin[2], tmax[2])};
		double tnear = std::max(std::max(t1[0], t1[1]), t1[2]);
		double tfar = std::min(std::min(t2[0], t2[1]), t2[2]);
		return tnear <= tfar;
	}
};

#endif //COURSE_PROJECT_RAY_HPP
