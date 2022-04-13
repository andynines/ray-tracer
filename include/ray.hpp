#ifndef COURSE_PROJECT_RAY_HPP
#define COURSE_PROJECT_RAY_HPP

#include <utility>

#include "math.hpp"

struct Ray {
	Vec3 origin;
	Vec3 dir;
	Ray(Vec3 origin, Vec3 dir) : origin(std::move(origin)), dir(std::move(dir).normalized()) {}
};

#endif //COURSE_PROJECT_RAY_HPP
