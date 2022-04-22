#include "sphere.hpp"

Sphere::Sphere() : SceneObj() {}

void Sphere::hit(const Ray& ray, const std::vector<PointLight>& pointLights, Hit& closestHit) const {
    const Vec3 localRayOrigin = invTrans * ray.origin;
    const Vec3 localRayDir = (invTrans.linear() * ray.dir).normalized();
    
    const double b = 2 * localRayOrigin.dot(localRayDir);
    const double c = localRayOrigin.dot(localRayOrigin) - 1;
    const double det = b * b - 4 * c;
    if (det < 0.0) return;
    
    const double t1 = (-b - std::sqrt(det)) / 2;
    const double t2 = (-b + std::sqrt(det)) / 2;
    const bool t1OutsideFov = t1 < 0.0;
    const bool t2OutsideFov = t2 < 0.0;
    if (t1OutsideFov && t2OutsideFov) return;
    else if (t1OutsideFov) closestHit.updateIfCloser(t2, surfColor);
    else if (t2OutsideFov) closestHit.updateIfCloser(t1, surfColor);
    else closestHit.updateIfCloser(std::min(t1, t2), surfColor);
}

void Sphere::load() {}
