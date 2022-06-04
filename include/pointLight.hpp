#ifndef COURSE_PROJECT_POINTLIGHT_HPP
#define COURSE_PROJECT_POINTLIGHT_HPP

#include "hit.hpp"
#include "math.hpp"

class PointLight {
public:
	PointLight(Vec3 pos, Rgb color);

	[[nodiscard]] Vec3 getPos() const;
	[[nodiscard]] Rgb shade(Hit& hit, const Vec3& camPos) const;

protected:
	[[nodiscard]] virtual Rgb calcLocalColor(const Vec3& towardsLight) const;

	Vec3 pos;
	Rgb color;
};

#endif //COURSE_PROJECT_POINTLIGHT_HPP
