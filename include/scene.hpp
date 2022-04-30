#ifndef COURSE_PROJECT_SCENE_HPP
#define COURSE_PROJECT_SCENE_HPP

#include "image.hpp"
#include "pointLight.hpp"
#include "sceneObject.hpp"

#include <memory>
#include <vector>

class Scene {
public:
    Scene();

    void setCam(const Vec3& camPos, const Vec3& camDir);
    void addObj(const std::shared_ptr<SceneObj>& obj);
    void addPointLight(const PointLight& pl);
	void constructBvh();
    void renderTo(Img& img) const;
    
private:
    static constexpr double fov = toRad(56);

	void becomeWorkerThread(int threadIndex, int stride, Img& img) const;

    Vec3 camPos, camDir, projPlaneCenter, right;
    double pxLength;
    std::vector<std::shared_ptr<SceneObj>> objs;
    std::vector<PointLight> pointLights;
};

#endif //COURSE_PROJECT_SCENE_HPP
