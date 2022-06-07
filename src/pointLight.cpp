#include "pointLight.hpp"

#include <utility>

PointLight::PointLight(Vec3 pos, Rgb color) : pos(std::move(pos)), color(std::move(color)) {}

Vec3 PointLight::getPos() const {
	return pos;
}

Rgb PointLight::shade(Hit& hit, const Vec3& camPos) const {
	Rgb result = hit.mat.ka * color.cwiseProduct(hit.mat.diffuse);
	if (hit.occluded) return result;

	Vec3 towardsLight = (pos - hit.pos).normalized();
	Rgb localColor = calcLocalColor(towardsLight);
	if (localColor.isZero()) return result;

	result += hit.mat.kd * localColor.cwiseProduct(hit.mat.diffuse) * std::max(hit.normal.dot(towardsLight), 0.0);

	Vec3 towardsCamera = (camPos - hit.pos).normalized();
	Vec3 reflDir = -reflect(towardsLight, hit.normal);
	result += hit.mat.ks * localColor.cwiseProduct(hit.mat.specular) * std::pow(std::max(towardsCamera.dot(reflDir), 0.0), hit.mat.shiny);

	result += hit.mat.kt * localColor.cwiseProduct(hit.mat.transmissive) * std::pow(std::max(towardsLight.dot(hit.refracDir), 0.0), hit.mat.highlight);

	return result;
}

Rgb PointLight::calcLocalColor(const Vec3& towardsLight) const {
	return color;
}
