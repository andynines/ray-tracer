#include "sphere.hpp"

Sphere::Sphere() : SceneObj(), radius(0) {}

void Sphere::hit(const Ray& ray, Hit& closestHit) const {
    const Vec3 towardsOrigin = ray.origin - center;
    const double b = 2 * ray.dir.dot(towardsOrigin);
    const double c = towardsOrigin.dot(towardsOrigin) - radius * radius;
    const double det = b * b - 4 * c;
    if (det < 0.0) return;
    
    const double t1 = (-b - std::sqrt(det)) / 2;
    const double t2 = (-b + std::sqrt(det)) / 2;
    const bool t1OutsideFov = t1 < 0.0;
    const bool t2OutsideFov = t2 < 0.0;
    if (t1OutsideFov && t2OutsideFov) return;

    double tclose;
    if (t1OutsideFov) tclose = t2;
    else if (t2OutsideFov) tclose = t1;
    else tclose = std::min(t1, t2);
    closestHit.updateIfCloser(tclose, mat, ((ray.origin + tclose * ray.dir) - center).normalized());
}

void Sphere::load() {
    center = trans * Vec3(0, 0, 0);
    radius = (trans.linear() * up).norm();
}
