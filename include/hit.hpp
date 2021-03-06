#ifndef COURSE_PROJECT_HIT_HPP
#define COURSE_PROJECT_HIT_HPP

#include "material.hpp"
#include "math.hpp"
#include "ray.hpp"

#include <memory>
#include <utility>

struct Hit {
    static constexpr double noHit = -1.0;
    
    double t;
	std::shared_ptr<Material> mat;
    Vec3 pos, normal, refracDir;
	bool occluded;
    
    Hit() : t(noHit), refracDir(zerov), occluded(true) {}
    
    void updateIfCloser(double newT, const std::shared_ptr<Material>& newMat, Vec3 newNormal, const Ray& ray) {
		// Invariant warning: we assume newT is not negative
		if (t >= 0.0 && t <= newT) return;
		t = newT;
		mat = newMat;
		normal = std::move(newNormal);
		pos = ray.origin + newT * ray.dir;
    }


};

#endif //COURSE_PROJECT_HIT_HPP
