#ifndef COURSE_PROJECT_IMAGEBUFFER_HPP
#define COURSE_PROJECT_IMAGEBUFFER_HPP

#include "math.hpp"

#include <vector>

class ImgBuf {
public:
	explicit ImgBuf(int res) : buf(res, std::vector<Rgb>(res, zero)) {}

	Rgb& at(int r, int c) {
		return buf[r][c];
	}

	[[nodiscard]] const Rgb& at(int r, int c) const {
		return buf[r][c];
	}

private:
	std::vector<std::vector<Rgb>> buf;
};

#endif //COURSE_PROJECT_IMAGEBUFFER_HPP
