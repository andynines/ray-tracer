#ifndef COURSE_PROJECT_POINTLIGHT_HPP
#define COURSE_PROJECT_POINTLIGHT_HPP

#include "math.hpp"
#include "rgb.hpp"

struct PointLight {
    Vec3 pos;
    Rgb color;
    
    PointLight(const Vec3& pos, const Rgb& color) : pos(pos), color(color) {}
};

#endif //COURSE_PROJECT_POINTLIGHT_HPP
