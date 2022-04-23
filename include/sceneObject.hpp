#ifndef COURSE_PROJECT_SCENEOBJECT_HPP
#define COURSE_PROJECT_SCENEOBJECT_HPP

#include "hit.hpp"
#include "math.hpp"
#include "ray.hpp"

#include <vector>

class SceneObj {
public:
    SceneObj() { trans.setIdentity(); }
    virtual ~SceneObj() = default;

    virtual void hit(const Ray& ray, Hit& closestHit) const = 0;
    virtual void load() = 0;
    
    void translate(const Vec3& t) { trans = trans.translate(trans.inverse() * t); }
    void rotate(double ang, const Vec3& ax) { trans = trans.rotate(AngleAxis(toRad(ang), ax)); }
    void scale(double c) { trans *= Scaling(c); }
    void color(const Rgb& c) { mat.color = c; }
    void setMaterial(double ka, double ks, double kd) {
        mat.ka = ka;
        mat.ks = ks;
        mat.kd = kd;
    }
    void setShiny(double s) { mat.shiny = s; }
    
protected:
    Transform trans;
    Material mat;
};

#endif //COURSE_PROJECT_SCENEOBJECT_HPP
