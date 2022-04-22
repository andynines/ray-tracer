#ifndef COURSE_PROJECT_SCENEOBJECT_HPP
#define COURSE_PROJECT_SCENEOBJECT_HPP

#include "hit.hpp"
#include "math.hpp"
#include "ray.hpp"
#include "rgb.hpp"

#include <vector>

class SceneObj {
public:
    SceneObj() { trans.setIdentity(); invTrans.setIdentity(); }

    virtual void hit(const Ray& ray, const std::vector<PointLight>& pointLights, Hit& closestHit) const = 0;
    virtual void load() = 0;
    
    void translate(const Vec3& t) { trans = trans.translate(invTrans * t); updateInvTrans(); }
    void rotate(double ang, const Vec3& ax) { trans = trans.rotate(AngleAxis(toRad(ang), ax)); updateInvTrans(); }
    void scale(double c) { trans *= Scaling(c); updateInvTrans(); }
    void color(const Rgb& c) { surfColor = c; }
    void setMaterial(double ka, double ks, double kd) {
        this->ka = ka;
        this->ks = ks;
        this->kd = kd;
    }
    void setShiny(double s) { shiny = s; }
    
protected:
    Transform trans, invTrans;
    Rgb surfColor;
    double ka, ks, kd, shiny;
    
    void updateInvTrans() { invTrans = trans.inverse(); }
};

#endif //COURSE_PROJECT_SCENEOBJECT_HPP
