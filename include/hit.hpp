#ifndef COURSE_PROJECT_HIT_HPP
#define COURSE_PROJECT_HIT_HPP

#include "material.hpp"
#include "math.hpp"

#include <utility>

struct Hit {
    static constexpr double noHit = -1.0;
    
    double t;
	Material mat;
    Vec3 normal;
    
    Hit() : t(noHit) {}
    
    void updateIfCloser(double t, Material mat, Vec3 normal) {
		// Invariant warning: we assume t is not negative
        if (this->t < 0.0 || this->t > t) {
            this->t = t;
            this->mat = std::move(mat);
            this->normal = std::move(normal);
        }
    }
};

#endif //COURSE_PROJECT_HIT_HPP
