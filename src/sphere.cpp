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
    bool t1OutsideFov = t1 < 0.0;
    bool t2OutsideFov = t2 < 0.0;
    if (t1OutsideFov && t2OutsideFov) return;

    double tclose;
    if (t1OutsideFov) tclose = t2;
    else if (t2OutsideFov) tclose = t1;
    else tclose = std::min(t1, t2);
	Vec3 normal = ((ray.origin + tclose * ray.dir) - center).normalized();
    closestHit.updateIfCloser(tclose, mat, normal);
}

void Sphere::load() {
    center = trans * zero;
    radius = (trans.linear() * up).norm();
}
