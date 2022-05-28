#include "math.hpp"
#include "plane.hpp"

void Plane::hit(const Ray& ray, Hit& closestHit) const {
	if (isZero(ray.dir.dot(normal))) return;
	const double t = normal.dot(point - ray.origin) / normal.dot(ray.dir);
	if (t < 0.0) return;
	closestHit.updateIfCloser(t, mat, normal, ray);
}

void Plane::load() {
	point = trans * zero;
	normal = trans.linear() * up;
}
