#ifndef COURSE_PROJECT_MATERIAL_HPP
#define COURSE_PROJECT_MATERIAL_HPP

#include "math.hpp"

struct Material {
	Rgb color;
	double ka, ks, kd, shiny;

	Material() : ka(0), ks(0), kd(0), shiny(0) {}
};

#endif //COURSE_PROJECT_MATERIAL_HPP
