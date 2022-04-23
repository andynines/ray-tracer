#ifndef COURSE_PROJECT_POINTLIGHT_HPP
#define COURSE_PROJECT_POINTLIGHT_HPP

#include <utility>

#include "hit.hpp"
#include "math.hpp"

struct PointLight {
    Vec3 pos;
    Rgb color;
    
    PointLight(Vec3 pos, Rgb color) : pos(std::move(pos)), color(std::move(color)) {}

	Rgb shade(Hit& hit, const Vec3& camPos, const Vec3& hitPos) const {
		Rgb ambient = hit.mat.ka * color;

		Vec3 towardsLight = (pos - hitPos).normalized();
		Rgb diffuse = hit.mat.kd * std::max(hit.normal.dot(towardsLight), 0.0) * color;

		return (ambient + diffuse).cwiseProduct(hit.mat.color);
	}
};

#endif //COURSE_PROJECT_POINTLIGHT_HPP
