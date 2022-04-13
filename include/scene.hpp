#ifndef COURSE_PROJECT_SCENE_HPP
#define COURSE_PROJECT_SCENE_HPP

#include "image.hpp"
#include "sceneObject.hpp"

#include <memory>
#include <vector>

class Scene {
public:
    void addObj(std::shared_ptr<SceneObj> obj);
    Img render(const Vec3& camPos, const Vec3& camDir) const;
    
private:
    std::vector<std::shared_ptr<SceneObj>> objs;
};

#endif //COURSE_PROJECT_SCENE_HPP
