#ifndef COURSE_PROJECT_SCENE_HPP
#define COURSE_PROJECT_SCENE_HPP

#include "image.hpp"
#include "pointLight.hpp"
#include "sceneObject.hpp"

#include <unordered_set>
#include <vector>

class Scene {
public:
    void setCam(const Vec3& pos, const Vec3& dir);
    void addObj(const std::shared_ptr<SceneObj>& obj);
    void addPointLight(const Vec3& pos, const Rgb& color);
	void addSpotLight(const Vec3& pos, const Rgb& color, const Vec3& dir, double cutoff, double sharpness);
	[[nodiscard]] Rgb calcPxColor(double x, double y) const;

private:
	[[nodiscard]] Rgb cast(const Ray& ray, int depth = 0) const;
	void hit(const Ray& ray, Hit& hit) const;

	Vec3 camPos, projPlaneCenter, right, camUp;
    std::unordered_set<std::shared_ptr<SceneObj>> objs;
    std::vector<std::shared_ptr<PointLight>> lights;
};

#endif //COURSE_PROJECT_SCENE_HPP
