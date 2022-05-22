#include "math.hpp"
#include "scene.hpp"
#include "smfModel.hpp"

void Scene::setCam(const Vec3& camPos, const Vec3& camDir) {
    this->camPos = camPos;
    projPlaneCenter = camPos + camDir;
    right = camDir.cross(up).normalized();
	camUp = right.cross(camDir).normalized();
}

void Scene::addObj(const std::shared_ptr<SceneObj>& obj) {
    objs.emplace_back(obj);
}

void Scene::addPointLight(const PointLight& pl) {
    pointLights.emplace_back(pl);
}

Rgb Scene::calcPxColor(double x, double y) const {
	Vec3 projPlaneHit = projPlaneCenter + (x * right) + (y * camUp);
	Ray pxRay(camPos, projPlaneHit - camPos);
	Hit closestHit;
	hit(pxRay, closestHit);
	if (closestHit.t == Hit::noHit) return zero;

	Rgb color = zero;
	for (const PointLight& light : pointLights) {
		static constexpr double shadowBias = 1e-3;
		Vec3 hitPos = pxRay.origin + closestHit.t * pxRay.dir;
		Vec3 shadowHitPos = hitPos + shadowBias * closestHit.normal;
		Vec3 hitToLight = light.pos - shadowHitPos;
		Ray shadowRay(shadowHitPos, hitToLight);
		Hit occlusionHit;
		hit(shadowRay, occlusionHit);
		bool occluded = occlusionHit.t != Hit::noHit && occlusionHit.t <= hitToLight.norm();
		color += light.shade(closestHit, camPos, hitPos, occluded);
	}
	return color;
}

void Scene::hit(const Ray &ray, Hit& hit) const {
	SmfModel::hitAll(ray, hit);
	for (const std::shared_ptr<SceneObj>& obj : objs)
		obj->hit(ray, hit);
}
