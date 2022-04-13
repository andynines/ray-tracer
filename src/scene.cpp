#include "math.hpp"
#include "scene.hpp"

void Scene::addObj(std::shared_ptr<SceneObj> obj) {
    objs.emplace_back(obj);
}

Img Scene::render(const Vec3& camPos, const Vec3& camDir) const {
    static constexpr double fov = toRad(56);
    static const double pxLength = 2 * std::tan(fov * 0.5) / Img::res;
    const Vec3 projPlaneCenter = camPos + camDir.normalized();
    const Vec3 right = (camDir.cross(up)).normalized();
    Img img;
    for (int i = 0; i < Img::res; i++) {
        for (int j = 0; j < Img::res; j++) {
            const Vec3 planeHit = projPlaneCenter + 
                ((j - Img::halfRes + 0.5) * pxLength * right) + 
                ((Img::halfRes - i - 0.5) * pxLength * up);
            const Ray pxRay(camPos, planeHit - camPos);
            for (const std::shared_ptr<SceneObj>& obj : objs)
                if (obj->hits(pxRay)) img.colorPixelAt(j, i, Rgb(255, 255, 255));
        }
    }
    return img;
}
