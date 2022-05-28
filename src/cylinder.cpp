#include "cylinder.hpp"

void Cylinder::hit(const Ray& ray, Hit& closestHit) const {
	Ray localRay(invTrans * ray.origin, (invTrans.linear() * ray.dir).normalized());
	hitSide(ray, localRay, closestHit);
	hitCap(ray, localRay, closestHit);
}

void Cylinder::load() {
	invTrans = trans.inverse();
	topNormal = (trans.linear() * up).normalized();
	bottomNormal = -topNormal;
	radius = (trans.linear() * up).norm();
	halfHeight = radius / 2;
}

void Cylinder::hitSide(const Ray &ray, const Ray& localRay, Hit &closestHit) const {
	double a = localRay.dir[0] * localRay.dir[0] + localRay.dir[2] * localRay.dir[2];
	double b = 2 * (localRay.origin[0] * localRay.dir[0] + localRay.origin[2] * localRay.dir[2]);
	double c = localRay.origin[0] * localRay.origin[0] + localRay.origin[2] * localRay.origin[2] - radius * radius;
	double discr = b * b - 4 * a * c;
	if (discr < 0.0) return;

	double localT1 = (-b + std::sqrt(discr)) / 2 / a;
	double localT2 = (-b - std::sqrt(discr)) / 2 / a;
	double t1 = ((trans * (localRay.origin + localT1 * localRay.dir)) - ray.origin).norm();
	double t2 = ((trans * (localRay.origin + localT2 * localRay.dir)) - ray.origin).norm();
	double tclose = calcPositiveMin(t1, t2);
	if (tclose < 0.0) return;

	double localTClose = (tclose == t1) ? localT1 : localT2;
	Vec3 localHitPos = localRay.origin + localTClose * localRay.dir;
	if (std::fabs(localHitPos[1]) > halfHeight) return;

	Vec3 normal = trans.linear() * Vec3(localHitPos[0], 0, localHitPos[2]).normalized();
	closestHit.updateIfCloser(tclose, mat, normal);
}

void Cylinder::hitCap(const Ray &ray, const Ray& localRay, Hit &closestHit) const {
	if (isZero(localRay.dir.dot(up))) return;

	double localT1 = (halfHeight - localRay.origin[1]) / localRay.dir[1];
	double localT2 = -(halfHeight + localRay.origin[1]) / localRay.dir[1];
	double t1 = ((trans * (localRay.origin + localT1 * localRay.dir)) - ray.origin).norm();
	double t2 = ((trans * (localRay.origin + localT2 * localRay.dir)) - ray.origin).norm();
	double tclose = calcPositiveMin(t1, t2);
	double localTClose = (tclose == t1) ? localT1 : localT2;
	Vec3 localHitPos = localRay.origin + localTClose * localRay.dir;
	if (Vec3(localHitPos[0], 0, localHitPos[2]).norm() > radius) return;

	Vec3 normal = (localRay.dir.dot(up) < 0.0) ? topNormal : bottomNormal;
	closestHit.updateIfCloser(tclose, mat, normal);
}
