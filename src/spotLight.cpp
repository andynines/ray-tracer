#include "spotLight.hpp"

#include <utility>

SpotLight::SpotLight(Vec3 pos, Rgb color, Vec3 dir, double cutoff, double sharpness) :
		PointLight(std::move(pos), std::move(color)),
		dir(std::move(dir)),
		cutoff(cutoff),
		sharpness(sharpness) {}

Rgb SpotLight::calcLocalColor(const Vec3 &towardsLight) const {
	double hitAng = std::acos(dir.dot(-towardsLight));
	if (hitAng > cutoff) return zero;
	else return color * std::pow(std::cos(pi / 2 * hitAng / cutoff), sharpness);
}
