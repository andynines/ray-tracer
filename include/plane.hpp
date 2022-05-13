#ifndef COURSE_PROJECT_PLANE_HPP
#define COURSE_PROJECT_PLANE_HPP

#include "sceneObject.hpp"

class Plane : public SceneObj {
public:
	void hit(const Ray& ray, Hit& closestHit) const override;
	void load() override;

private:
	Vec3 point, normal;
};

#endif //COURSE_PROJECT_PLANE_HPP
