#ifndef COURSE_PROJECT_SPHERE_HPP
#define COURSE_PROJECT_SPHERE_HPP

#include "math.hpp"
#include "sceneObject.hpp"

class Sphere : public SceneObj {
public:
    Sphere();

	void hit(const Ray& ray, Hit& closestHit) const override;
    void load() override;

private:
    Vec3 center;
    double radius;
};

#endif //COURSE_PROJECT_SPHERE_HPP
