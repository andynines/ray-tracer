#ifndef COURSE_PROJECT_POINTLIGHT_HPP
#define COURSE_PROJECT_POINTLIGHT_HPP

#include <utility>

#include "hit.hpp"
#include "math.hpp"

struct PointLight {
    Vec3 pos;
    Rgb color;

	PointLight(Vec3 pos, Rgb color);

	Rgb shade(Hit& hit, const Vec3& camPos, const Vec3& hitPos) const;
};

#endif //COURSE_PROJECT_POINTLIGHT_HPP
