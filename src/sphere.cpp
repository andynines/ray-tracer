#include "sphere.hpp"

Sphere::Sphere() : SceneObj() {}

Rgb Sphere::hit(const Ray& ray, const std::vector<PointLight>& pointLights) const {
    const Vec3 localRayOrigin = invTrans * ray.origin;
    const Vec3 localRayDir = (invTrans.linear() * ray.dir).normalized();
    const double b = 2 * localRayOrigin.dot(localRayDir);
    const double c = localRayOrigin.dot(localRayOrigin) - 1;
    const double det = b * b - 4 * c;
    if (det < 0.0) return Rgb();
    else return ambient;
}
