#ifndef COURSE_PROJECT_SCENE_HPP
#define COURSE_PROJECT_SCENE_HPP

#include "image.hpp"
#include "sceneObject.hpp"

#include <memory>
#include <vector>

class Scene {
public:
    Scene(const Vec3& camPos, const Vec3& camDir);

    void addObj(std::shared_ptr<SceneObj> obj);
    Img render() const;
    
private:
    Vec3 camPos, camDir;

    std::vector<std::shared_ptr<SceneObj>> objs;
};

#endif //COURSE_PROJECT_SCENE_HPP
