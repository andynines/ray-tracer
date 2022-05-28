#ifndef COURSE_PROJECT_HIT_HPP
#define COURSE_PROJECT_HIT_HPP

#include "material.hpp"
#include "math.hpp"
#include "ray.hpp"

#include <utility>

struct Hit {
    static constexpr double noHit = -1.0;
    
    double t;
	Material mat;
    Vec3 pos, normal;
	bool occluded;
    
    Hit() : t(noHit), occluded(true) {}
    
    void updateIfCloser(double newT, Material newMat, Vec3 newNormal, const Ray& ray) {
		// Invariant warning: we assume t is not negative
        if (t < 0.0 || t > newT) {
            t = newT;
            mat = std::move(newMat);
            normal = std::move(newNormal);
			pos = ray.origin + newT * ray.dir;
        }
    }


};

#endif //COURSE_PROJECT_HIT_HPP
