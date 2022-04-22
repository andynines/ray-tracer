#ifndef COURSE_PROJECT_HIT_HPP
#define COURSE_PROJECT_HIT_HPP

#include "rgb.hpp"

struct Hit {
    static constexpr double noHit = -1.0;
    
    double t;
    Rgb color;
    
    Hit() : t(noHit), color(Rgb()) {}
    Hit(double t, Rgb color) : t(t), color(color) {}
    
    void updateIfCloser(double t, Rgb color) {
        if (this->t < 0.0 || this->t > t) {
            this->t = t;
            this->color = color;
        }
    }
};

#endif //COURSE_PROJECT_HIT_HPP
