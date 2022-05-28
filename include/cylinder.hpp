#ifndef COURSE_PROJECT_CYLINDER_HPP
#define COURSE_PROJECT_CYLINDER_HPP

#include "plane.hpp"
#include "sceneObject.hpp"

class Cylinder : public SceneObj {
public:
	void hit(const Ray& ray, Hit& closestHit) const override;
	void load() override;

private:
	void hitSide(const Ray& ray, const Ray& localRay, Hit& closestHit) const;
	void hitCap(const Ray& ray, const Ray& localRay, Hit& closestHit) const;

	Transform invTrans;
	double radius, halfHeight;
	Vec3 topNormal, bottomNormal;
};

#endif //COURSE_PROJECT_CYLINDER_HPP
