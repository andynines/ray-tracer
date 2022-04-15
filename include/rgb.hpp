#ifndef COURSE_PROJECT_RGB_HPP
#define COURSE_PROJECT_RGB_HPP

#include <cstdint>

struct Rgb {
	uint8_t r, g, b;
    
    Rgb() : r(0), g(0), b(0) {}
	Rgb(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    
    void operator+=(const Rgb& other) { r += other.r; g += other.g; b += other.b; }
};

#endif //COURSE_PROJECT_RGB_HPP
