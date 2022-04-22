#ifndef COURSE_PROJECT_SPHERE_HPP
#define COURSE_PROJECT_SPHERE_HPP

#include "math.hpp"
#include "pointLight.hpp"
#include "rgb.hpp"
#include "sceneObject.hpp"

#include <vector>

class Sphere : public SceneObj {
public:
    Sphere();

	void hit(const Ray& ray, const std::vector<PointLight>& pointLights, Hit& closestHit) const override;
    void load() override;
};

#endif //COURSE_PROJECT_SPHERE_HPP
