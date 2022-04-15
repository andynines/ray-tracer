#ifndef COURSE_PROJECT_SCENEOBJECT_HPP
#define COURSE_PROJECT_SCENEOBJECT_HPP

#include "math.hpp"
#include "ray.hpp"
#include "rgb.hpp"

class SceneObj {
public:
    SceneObj() { trans.setIdentity(); }

    virtual Rgb hit(const Ray& ray) const = 0;
    
    void translate(const Vec3& t) { trans = trans.translate(t); updateInvTrans(); }
    void rotate(double ang, const Vec3& ax) { trans = trans.rotate(AngleAxis(ang, ax)); updateInvTrans(); }
    void scale(double c) { trans *= Scaling(c); updateInvTrans(); }
    void paint(const Rgb& c) { color = c; }
    
protected:
    Transform trans, invTrans;
    Rgb color;
    
    void updateInvTrans() { invTrans = trans.inverse(); }
};

#endif //COURSE_PROJECT_SCENEOBJECT_HPP
