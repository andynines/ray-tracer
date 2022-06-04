#ifndef COURSE_PROJECT_SCENEOBJECT_HPP
#define COURSE_PROJECT_SCENEOBJECT_HPP

#include "hit.hpp"
#include "material.hpp"
#include "math.hpp"
#include "ray.hpp"

#include <utility>
#include <vector>

class SceneObj {
public:
    SceneObj() { trans.setIdentity(); }
    virtual ~SceneObj() = default;

    virtual void hit(const Ray& ray, Hit& closestHit) const = 0;
    virtual void load() = 0;
    
    void translate(const Vec3& t) { trans = trans.translate(t); }

    void rotate(double ang, const Vec3& ax) { trans = trans.rotate(AngleAxis(ang, ax)); }

	void scale(double c) { trans *= Scaling(c); }

    void setAmbient(double ka) { mat.ka = ka; }

	void setDiffuse(double kd, Rgb diffuse) {
		mat.kd = kd;
		mat.diffuse = std::move(diffuse);
	}

	void setSpecular(double ks, Rgb specular) {
		mat.ks = ks;
		mat.specular = std::move(specular);
	}

    void setShiny(double s) { mat.shiny = s; }

	void setReflective(double r) { mat.reflective = r; }

protected:
    Transform trans;
    Material mat;
};

#endif //COURSE_PROJECT_SCENEOBJECT_HPP
