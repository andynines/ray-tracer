#ifndef COURSE_PROJECT_IMG_HPP
#define COURSE_PROJECT_IMG_HPP

#include "imageBuffer.hpp"
#include "math.hpp"
#include "stdFilesystem.hpp"

#include <array>

class Img {
public:
	static constexpr int res = 512;
	static constexpr int halfRes = res / 2;

	Img();

	void setColorAt(int r, int c, const Rgb& rgb);
	void writePng(const fs::path& png);

private:
    ImgBuf px;
};

#endif //COURSE_PROJECT_IMG_HPP
