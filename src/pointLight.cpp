#include "pointLight.hpp"

PointLight::PointLight(Vec3 pos, Rgb color) : pos(std::move(pos)), color(std::move(color)) {}

Rgb PointLight::shade(Hit& hit, const Vec3& camPos, const Vec3& hitPos) const {
	Rgb ambient = hit.mat.ka * color;

	Vec3 towardsLight = (pos - hitPos).normalized();
	Rgb diffuse = hit.mat.kd * std::max(hit.normal.dot(towardsLight), 0.0) * color;

	Vec3 towardsCamera = (camPos - hitPos).normalized();
	Vec3 reflDir = (2 * hit.normal.dot(towardsLight) * hit.normal) - towardsLight;
	Rgb specular = hit.mat.ks * std::pow(std::max(towardsCamera.dot(reflDir), 0.0), hit.mat.shiny) * color;

	return (ambient + diffuse + specular).cwiseProduct(hit.mat.color);
}
