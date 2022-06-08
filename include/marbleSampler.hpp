#ifndef COURSE_PROJECT_MARBLESAMPLER_HPP
#define COURSE_PROJECT_MARBLESAMPLER_HPP

#include "image.hpp"

class MarbleSampler {
public:
	MarbleSampler();

	void generateTestImage();

private:
	static constexpr int width = Img::res, height = Img::res, depth = 1;

	void generate();
	[[nodiscard]] double smooth(double x, double y, double z) const;
	[[nodiscard]] double turbulence(double x, double y, double z) const;

	double noise[depth][height][width];
};

#endif //COURSE_PROJECT_MARBLESAMPLER_HPP
