#ifndef COURSE_PROJECT_MATERIAL_HPP
#define COURSE_PROJECT_MATERIAL_HPP

#include "math.hpp"

struct Material {
	Rgb diffuse, specular, transmissive;
	double ka, ks, kd, kt, shiny, reflective;

	Material() : ka(0), ks(0), kd(0), kt(0), shiny(0), reflective(0) {}
};

#endif //COURSE_PROJECT_MATERIAL_HPP
