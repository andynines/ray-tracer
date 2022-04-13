#include "sphere.hpp"

Sphere::Sphere() : SceneObj() {}

bool Sphere::hits(const Ray& ray) const {
    const Vec3 localRayOrigin = invTrans * ray.origin;
    const Vec3 localRayDir = (invTrans.linear() * ray.dir).normalized();
    const double x0 = localRayOrigin[0];
    const double y0 = localRayOrigin[1];
    const double z0 = localRayOrigin[2];
    const double xd = localRayDir[0];
    const double yd = localRayDir[1];
    const double zd = localRayDir[2];
    const double b = 2 * (xd * x0 + yd * y0 + zd * z0);
    const double c = x0 * x0 + y0 * y0 + z0 * z0 - 1;
    return b * b >= 4 * c;
}
