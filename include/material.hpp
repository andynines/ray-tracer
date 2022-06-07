#ifndef COURSE_PROJECT_MATERIAL_HPP
#define COURSE_PROJECT_MATERIAL_HPP

#include "math.hpp"

struct Material {
	Rgb diffuse, specular, transmissive;
	double ka, ks, kd, kt, kr, shiny, highlight;

	Material() : diffuse(zerov), specular(zerov), transmissive(zerov), ka(0), ks(0), kd(0), kt(0), kr(0), shiny(0), highlight(0) {}
};

#endif //COURSE_PROJECT_MATERIAL_HPP
