#include "math.hpp"
#include "scene.hpp"
#include "smfModel.hpp"

#include <thread>

Scene::Scene() :
	pxLength(2 * std::tan(fov * 0.5) / Img::res),
	primaryRayColors(primaryRayBufRes) {}

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

void Scene::renderTo(Img& img) {
	numRaysCast = 0;
	unsigned int numThreads = std::thread::hardware_concurrency();
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

	// TODO: Parallelize
	for (int i = 0; i < Img::res; i++) {
		for (int j = 0; j < Img::res; j++) {
			Rgb a = primaryRayColors.at(i, j);
			Rgb b = primaryRayColors.at(i+1, j);
			Rgb c = primaryRayColors.at(i, j+1);
			Rgb d = primaryRayColors.at(i+1, j+1);
			if (isWithinTolerance(a, b, c, d)) {
				img.setColorAt(i, j, (a + b + c + d) / 4);
			} else {
				img.setColorAt(i, j, (
						resolve(i, j) +
						resolve(i + 0.5, j) +
						resolve(i, j + 0.5) +
						resolve(i + 0.5, j + 0.5)
						) / 4);
			}
		}
	}
}

void Scene::becomeWorkerThread(int threadIndex, int stride, Img& img) {
	for (int i = threadIndex; i < primaryRayBufRes; i += stride)
		for (int j = 0; j < primaryRayBufRes; j++)
			primaryRayColors.at(i, j) = calcPxColor(i, j);
}

Rgb Scene::resolve(double x, double y, double d) {
	static constexpr double minD = 0.25;
	Rgb rgb0 = (isWhole(x) && isWhole(y)) ?
			primaryRayColors.at(static_cast<int>(x), static_cast<int>(y)) :
			calcPxColor(x, y);
	Rgb rgb1 = calcPxColor(x + d, y);
	Rgb rgb2 = calcPxColor(x, y + d);
	Rgb rgb3 = calcPxColor(x + d, y + d);
	if (d > minD && !isWithinTolerance(rgb0, rgb1, rgb2, rgb3)) {
		double nextD = d / 2;
		return (
				resolve(x, y, nextD) +
				resolve(x + nextD, y, nextD) +
				resolve(x, y + nextD, nextD) +
				resolve(x + nextD, y + nextD)
				) / 4;
	}
	return (rgb0 + rgb1 + rgb2 + rgb3) / 4;
}

Rgb Scene::calcPxColor(double x, double y) {
	Vec3 projPlaneHit = projPlaneCenter +
						((x - Img::halfRes) * pxLength * right) +
						((Img::halfRes - y) * pxLength * up);
	Ray pxRay(camPos, projPlaneHit - camPos);
	Rgb pxColor = cast(pxRay);
	return pxColor;
}

Rgb Scene::cast(const Ray& ray) {
	numRaysCast++;
	Hit closestHit;
	SmfModel::hitAll(ray, closestHit);
	for (const std::shared_ptr<SceneObj>& obj : objs)
		obj->hit(ray, closestHit);
	Rgb color = zero;
	for (const PointLight& light : pointLights)
		color += light.shade(closestHit, camPos, ray.origin + closestHit.t * ray.dir);
	return color;
}

bool Scene::isWithinTolerance(const Rgb& a, const Rgb& b, const Rgb& c, const Rgb& d) {
	static constexpr double tol = 0.05;
	return true;
	return (a - b).lpNorm<1>() <= tol &&
			(a - c).lpNorm<1>() <= tol &&
			(b - d).lpNorm<1>() <= tol &&
			(c - d).lpNorm<1>() <= tol;
}

constexpr bool Scene::isWhole(double d) {
	return std::floor(d) == d;
}
