#include "math.hpp"
#include "scene.hpp"
#include "smfModel.hpp"

#include <thread>

void Scene::setCam(const Vec3& camPos, const Vec3& camDir) {
    this->camPos = camPos;
    projPlaneCenter = camPos + camDir;
    right = camDir.cross(up).normalized();
}

void Scene::addObj(const std::shared_ptr<SceneObj>& obj) {
    objs.emplace_back(obj);
}

void Scene::addPointLight(const PointLight& pl) {
    pointLights.emplace_back(pl);
}

Rgb Scene::calcPxColor(double x, double y) const {
	Vec3 projPlaneHit = projPlaneCenter + (x * right) + (y * up);
	Ray pxRay(camPos, projPlaneHit - camPos);
	Rgb pxColor = cast(pxRay);
	return pxColor;
}

Rgb Scene::cast(const Ray& ray) const {
	Hit closestHit;
	SmfModel::hitAll(ray, closestHit);
	for (const std::shared_ptr<SceneObj>& obj : objs)
		obj->hit(ray, closestHit);
	if (closestHit.t == Hit::noHit) return zero;

	Rgb color = zero;
	for (const PointLight& light : pointLights) {
		Vec3 hitPos = ray.origin + closestHit.t * ray.dir;
		color += light.shade(closestHit, camPos, hitPos);
	}
	return color;
}
