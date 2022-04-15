#ifndef COURSE_PROJECT_SCENEOBJECT_HPP
#define COURSE_PROJECT_SCENEOBJECT_HPP

#include "math.hpp"
#include "ray.hpp"
#include "rgb.hpp"

#include <vector>

class SceneObj {
public:
    SceneObj() { trans.setIdentity(); invTrans.setIdentity(); }

    virtual Rgb hit(const Ray& ray, const std::vector<PointLight>& pointLights) const = 0;
    
    void translate(const Vec3& t) { trans = trans.translate(invTrans * t); updateInvTrans(); }
    void rotate(double ang, const Vec3& ax) { trans = trans.rotate(AngleAxis(toRad(ang), ax)); updateInvTrans(); }
    void scale(double c) { trans *= Scaling(c); updateInvTrans(); }
    void style(const Rgb& ambient, const Rgb& specular, const Rgb& diffuse, double shiny) {
        this->ambient = ambient;
        this->specular = specular;
        this->diffuse = diffuse;
        this->shiny = shiny;
    }
    
protected:
    Transform trans, invTrans;
    Rgb ambient, specular, diffuse;
    double shiny;
    
    void updateInvTrans() { invTrans = trans.inverse(); }
};

#endif //COURSE_PROJECT_SCENEOBJECT_HPP
