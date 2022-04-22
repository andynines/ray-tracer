#ifndef COURSE_PROJECT_RGB_HPP
#define COURSE_PROJECT_RGB_HPP

struct Rgb { // TODO: Get rid of me. I'm just a Vec3.
	double r, g, b;
    
    Rgb() : r(0.0), g(0.0), b(0.0) {}
	Rgb(double r, double g, double b) : r(r), g(g), b(b) {}
    
    void operator+=(const Rgb& other) { r += other.r; g += other.g; b += other.b; }
};

#endif //COURSE_PROJECT_RGB_HPP
