#ifndef COURSE_PROJECT_SPHERE_HPP
#define COURSE_PROJECT_SPHERE_HPP

#include "math.hpp"
#include "sceneObject.hpp"
#include "stdFilesystem.hpp"
#include "textureMaterial.hpp"

class Sphere : public SceneObj {
public:
    Sphere();
	explicit Sphere(const fs::path& tex) : SceneObj(std::make_unique<TexMaterial>(tex)) {}

	void hit(const Ray& ray, Hit& closestHit) const override;
    void load() override;

private:
    Vec3 center;
    double radius{};
};

#endif //COURSE_PROJECT_SPHERE_HPP
