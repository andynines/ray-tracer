#ifndef COURSE_PROJECT_IMG_HPP
#define COURSE_PROJECT_IMG_HPP

#include "imageBuffer.hpp"
#include "math.hpp"
#include "stdFilesystem.hpp"

#include <ImageMagick-6/Magick++.h>

#include <mutex>

class Img {
public:
	static constexpr int res = 512;

	Img();

	void setColorAt(int x, int y, const Rgb& c);
	void writePng(const fs::path& png);

private:
	Magick::Image img;
};

#endif //COURSE_PROJECT_IMG_HPP
