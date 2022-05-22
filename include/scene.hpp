#ifndef COURSE_PROJECT_SCENE_HPP
#define COURSE_PROJECT_SCENE_HPP

#include "image.hpp"
#include "pointLight.hpp"
#include "sceneObject.hpp"

#include <vector>

class Scene {
public:
    void setCam(const Vec3& camPos, const Vec3& camDir);
    void addObj(const std::shared_ptr<SceneObj>& obj);
    void addPointLight(const PointLight& pl);
	[[nodiscard]] Rgb calcPxColor(double x, double y) const;

private:
	void hit(const Ray& ray, Hit& hit) const;

	Vec3 camPos, projPlaneCenter, right, camUp;
    std::vector<std::shared_ptr<SceneObj>> objs;
    std::vector<PointLight> pointLights;
};

#endif //COURSE_PROJECT_SCENE_HPP
