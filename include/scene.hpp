#ifndef COURSE_PROJECT_SCENE_HPP
#define COURSE_PROJECT_SCENE_HPP

#include "image.hpp"
#include "pointLight.hpp"
#include "sceneObject.hpp"

#include <memory>
#include <vector>

class Scene {
public:
    void setCam(const Vec3& camPos, const Vec3& camDir);
    void addObj(std::shared_ptr<SceneObj> obj);
    void addPointLight(const PointLight& pl);
    void renderTo(Img& img) const;
    
private:
    static constexpr double fov = toRad(56);

    Vec3 camPos, camDir;
    std::vector<std::shared_ptr<SceneObj>> objs;
    std::vector<PointLight> pointLights;
};

#endif //COURSE_PROJECT_SCENE_HPP
