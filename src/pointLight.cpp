#include "pointLight.hpp"

PointLight::PointLight(Vec3 pos, Rgb color) : pos(std::move(pos)), color(std::move(color)) {}

Rgb PointLight::shade(Hit& hit, const Vec3& camPos) const {
	Rgb result = hit.mat.ka * color.cwiseProduct(hit.mat.diffuse);
	if (hit.occluded) return result;

	Vec3 towardsLight = (pos - hit.pos).normalized();
	result += hit.mat.kd * color.cwiseProduct(hit.mat.diffuse) * std::max(hit.normal.dot(towardsLight), 0.0);

	Vec3 towardsCamera = (camPos - hit.pos).normalized();
	Vec3 reflDir = -reflect(towardsLight, hit.normal);
	result += hit.mat.ks * color.cwiseProduct(hit.mat.specular) * std::pow(std::max(towardsCamera.dot(reflDir), 0.0), hit.mat.shiny);

	return result;
}
