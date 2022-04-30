#include "math.hpp"
#include "scene.hpp"

#include <thread>

Scene::Scene() : pxLength(2 * std::tan(fov * 0.5) / Img::calcRes) {}

void Scene::setCam(const Vec3& camPos, const Vec3& camDir) {
    this->camPos = camPos;
    this->camDir = camDir;
    projPlaneCenter = camPos + camDir;
    right = camDir.cross(up).normalized();
}

void Scene::addObj(const std::shared_ptr<SceneObj>& obj) {
    objs.emplace_back(obj);
}

void Scene::addPointLight(const PointLight& pl) {
    pointLights.emplace_back(pl);
}

void Scene::constructBvh() {

}

void Scene::renderTo(Img& img) const {
	const unsigned int numThreads = std::thread::hardware_concurrency();
	if (numThreads == 0) {
		becomeWorkerThread(0, 1, img);
		return;
	}

	std::vector<std::thread> threads;
	threads.reserve(numThreads);
	for (unsigned int i = 0; i < numThreads; i++)
		threads.emplace_back(&Scene::becomeWorkerThread, this, i, numThreads, std::ref(img));
	for (std::thread& t : threads)
		t.join();
}

void Scene::becomeWorkerThread(int threadIndex, int stride, Img& img) const {
	for (int i = threadIndex; i < Img::calcRes; i += stride) {
		for (int j = 0; j < Img::calcRes; j++) {
			const Vec3 projPlaneHit = projPlaneCenter +
									  ((j - Img::halfCalcRes + 0.5) * pxLength * right) +
									  ((Img::halfCalcRes - i - 0.5) * pxLength * up);
			const Ray pxRay(camPos, projPlaneHit - camPos);
			Hit closestHit;
			for (const std::shared_ptr<SceneObj>& obj : objs)
				if (obj->hitsAabb(pxRay))
					obj->hit(pxRay, closestHit);
			Rgb pxColor = zero;
			for (const PointLight& light : pointLights)
				pxColor += light.shade(closestHit, camPos, pxRay.origin + closestHit.t * pxRay.dir);
			img.setColorAt(j, i, pxColor);
		}
	}
}
