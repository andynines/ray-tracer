#ifndef COURSE_PROJECT_SPOTLIGHT_HPP
#define COURSE_PROJECT_SPOTLIGHT_HPP

#include "pointLight.hpp"

class SpotLight : public PointLight {
public:
	SpotLight(Vec3 pos, Rgb color, Vec3 dir, double cutoff, double sharpness);

private:
	[[nodiscard]] Rgb calcLocalColor(const Vec3& towardsLight) const override;

	Vec3 dir;
	double cutoff, sharpness;
};

#endif //COURSE_PROJECT_SPOTLIGHT_HPP
