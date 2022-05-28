#include "sphere.hpp"

Sphere::Sphere() : SceneObj(), radius(0) {}

void Sphere::hit(const Ray& ray, Hit& closestHit) const {
    Vec3 towardsOrigin = ray.origin - center;
    double b = 2 * ray.dir.dot(towardsOrigin);
    double c = towardsOrigin.dot(towardsOrigin) - radius * radius;
    double det = b * b - 4 * c;
    if (det < 0.0) return;
    
    double t1 = (-b - std::sqrt(det)) / 2;
    double t2 = (-b + std::sqrt(det)) / 2;
    double tclose = calcPositiveMin(t1, t2);
	if (tclose < 0.0) return;

	Vec3 normal = ((ray.origin + tclose * ray.dir) - center).normalized();
    closestHit.updateIfCloser(tclose, mat, normal);
}

void Sphere::load() {
    center = trans * zero;
    radius = (trans.linear() * up).norm();
}
