#ifndef COURSE_PROJECT_SPHERE_HPP
#define COURSE_PROJECT_SPHERE_HPP

#include "math.hpp"
#include "rgb.hpp"
#include "sceneObject.hpp"

#include <iostream>

class Sphere : public SceneObj {
public:
    Sphere();

	Rgb hit(const Ray& ray) const override;
};

#endif //COURSE_PROJECT_SPHERE_HPP
