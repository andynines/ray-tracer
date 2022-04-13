#ifndef COURSE_PROJECT_RGB_HPP
#define COURSE_PROJECT_RGB_HPP

#include <cstdint>

struct Rgb {
	uint8_t r, g, b;
	Rgb(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

#endif //COURSE_PROJECT_RGB_HPP
