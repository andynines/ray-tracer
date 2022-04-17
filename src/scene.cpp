#include "math.hpp"
#include "scene.hpp"

void Scene::setCam(const Vec3& camPos, const Vec3& camDir) {
    this->camPos = camPos;
    this->camDir = camDir;
}

void Scene::addObj(std::shared_ptr<SceneObj> obj) {
    objs.emplace_back(obj);
}

void Scene::addPointLight(const PointLight& pl) {
    pointLights.emplace_back(pl);
}

void Scene::renderTo(Img& img) const {
    static const double pxLength = 2 * std::tan(fov * 0.5) / Img::res;
    const Vec3 projPlaneCenter = camPos + camDir.normalized();
    const Vec3 right = (camDir.cross(up)).normalized();
    for (int i = 0; i < Img::res; i++) {
        for (int j = 0; j < Img::res; j++) {
            const Vec3 projPlaneHit = projPlaneCenter + 
                ((j - Img::halfRes + 0.5) * pxLength * right) + 
                ((Img::halfRes - i - 0.5) * pxLength * up);
            const Ray pxRay(camPos, projPlaneHit - camPos);
            for (const std::shared_ptr<SceneObj>& obj : objs)
                img.addColorAt(j, i, obj->hit(pxRay, pointLights));
        }
    }
}
