#ifndef COURSE_PROJECT_POINTLIGHT_HPP
#define COURSE_PROJECT_POINTLIGHT_HPP

#include <utility>

#include "hit.hpp"
#include "math.hpp"

struct PointLight {
	static constexpr double lightStrength = 0.1;

    Vec3 pos;
    Rgb color;

	PointLight(Vec3 pos, Rgb color);

	[[nodiscard]] Rgb shade(Hit& hit, const Vec3& camPos) const;
};

#endif //COURSE_PROJECT_POINTLIGHT_HPP
