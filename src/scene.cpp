#include "math.hpp"
#include "scene.hpp"

Scene::Scene() : pxLength(2 * std::tan(fov * 0.5) / Img::res) {}

void Scene::setCam(const Vec3& camPos, const Vec3& camDir) {
    this->camPos = camPos;
    this->camDir = camDir;
    projPlaneCenter = camPos + camDir.normalized();
    right = camDir.cross(up).normalized();
}

void Scene::addObj(const std::shared_ptr<SceneObj>& obj) {
    objs.emplace_back(obj);
}

void Scene::addPointLight(const PointLight& pl) {
    pointLights.emplace_back(pl);
}

void Scene::renderTo(Img& img) const {
    for (int i = 0; i < Img::res; i++) {
        for (int j = 0; j < Img::res; j++) {
            const Vec3 projPlaneHit = projPlaneCenter + 
                ((j - Img::halfRes + 0.5) * pxLength * right) + 
                ((Img::halfRes - i - 0.5) * pxLength * up);
            const Ray pxRay(camPos, projPlaneHit - camPos);
            Hit closestHit;
            for (const std::shared_ptr<SceneObj>& obj : objs)
				obj->hit(pxRay, closestHit);
			Rgb pxColor = zero;
			for (const PointLight& light : pointLights)
				pxColor += light.shade(closestHit, camPos, pxRay.origin + closestHit.t * pxRay.dir);
            img.setColorAt(j, i, pxColor);
        }
    }
}
