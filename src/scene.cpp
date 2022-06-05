#include "math.hpp"
#include "scene.hpp"
#include "spotLight.hpp"

void Scene::setCam(const Vec3& pos, const Vec3& dir) {
    camPos = pos;
    projPlaneCenter = pos + dir;
    right = dir.cross(up).normalized();
	camUp = right.cross(dir).normalized();
}

void Scene::addObj(const std::shared_ptr<SceneObj>& obj) {
    objs.emplace(obj);
}

void Scene::addPointLight(const Vec3& pos, const Rgb& color) {
    lights.emplace_back(std::make_shared<PointLight>(pos, color));
}

void Scene::addSpotLight(const Vec3& pos, const Rgb& color, const Vec3& dir, double cutoff, double sharpness) {
	lights.emplace_back(std::make_shared<SpotLight>(pos, color, dir, cutoff, sharpness));
}

Rgb Scene::calcPxColor(double x, double y) const {
	Vec3 projPlaneHit = projPlaneCenter + (x * right) + (y * camUp);
	Ray pxRay(camPos, (projPlaneHit - camPos).normalized());
	return cast(pxRay);
}

Rgb Scene::cast(const Ray& ray, int reflectionDepth) const {
	Hit closestHit;
	hit(ray, closestHit);
	if (closestHit.t == Hit::noHit) return zero;

	Rgb color = zero;

	static constexpr double bias = 1e-3;
	Vec3 biasedHitPos = closestHit.pos + bias * closestHit.normal;

	static constexpr int maxReflectionDepth = 5;
	if (closestHit.mat.reflective > 0.0 && reflectionDepth <= maxReflectionDepth) {
		Vec3 reflDir = reflect(ray.dir, closestHit.normal);
		Ray reflectionRay(biasedHitPos, reflDir);
		color += closestHit.mat.reflective * cast(reflectionRay, reflectionDepth + 1).cwiseProduct(closestHit.mat.specular);
	}

	for (const std::shared_ptr<PointLight>& light : lights) {
		Vec3 hitToLight = light->getPos() - biasedHitPos;
		Ray shadowRay(biasedHitPos, hitToLight.normalized());
		Hit occlusionHit;
		hit(shadowRay, occlusionHit);
		closestHit.occluded = (occlusionHit.t != Hit::noHit) && (occlusionHit.t <= hitToLight.norm());
		color += light->shade(closestHit, camPos);
	}
	return color;
}

void Scene::hit(const Ray &ray, Hit& hit) const {
	for (const std::shared_ptr<SceneObj>& obj : objs)
		obj->hit(ray, hit);
}
