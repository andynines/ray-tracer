#ifndef COURSE_PROJECT_POINTLIGHT_HPP
#define COURSE_PROJECT_POINTLIGHT_HPP

#include "math.hpp"
#include "rgb.hpp"

struct PointLight {
    static constexpr double ka = 0.1;
    static constexpr double ks = 1.0;
    static constexpr double kd = 0.5;
    
    Vec3 pos;
    Rgb color;
    
    PointLight(const Vec3& pos, const Rgb& color) : pos(pos), color(color) {}
};

#endif //COURSE_PROJECT_POINTLIGHT_HPP
