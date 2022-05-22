#ifndef COURSE_PROJECT_IMAGEBUFFER_HPP
#define COURSE_PROJECT_IMAGEBUFFER_HPP

#include "math.hpp"

#include <vector>

class ImgBuf {
public:
	explicit ImgBuf(int res) : buf(res, std::vector<Rgb>(res, nullRgb)) {}

	Rgb& at(int x, int y) {
		return buf[x][y];
	}

	[[nodiscard]] const Rgb& at(int x, int y) const {
		return buf[x][y];
	}

private:
	std::vector<std::vector<Rgb>> buf;
};

#endif //COURSE_PROJECT_IMAGEBUFFER_HPP
