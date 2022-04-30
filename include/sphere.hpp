#ifndef COURSE_PROJECT_SPHERE_HPP
#define COURSE_PROJECT_SPHERE_HPP

#include "math.hpp"
#include "pointLight.hpp"
#include "sceneObject.hpp"

#include <vector>

class Sphere : public SceneObj {
public:
    Sphere();

	void hit(const Ray& ray, Hit& closestHit) const override;
	bool hitsAabb(const Ray& ray) const override;
    void load() override;

private:
    Vec3 center, aabbMin, aabbMax;
    double radius;
};

#endif //COURSE_PROJECT_SPHERE_HPP
