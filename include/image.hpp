#ifndef COURSE_PROJECT_IMG_HPP
#define COURSE_PROJECT_IMG_HPP

#include "rgb.hpp"

#include <ImageMagick-6/Magick++.h>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class Img {
public:
	static constexpr int res = 512;
    static constexpr int halfRes = res / 2;

	Img();
	void colorPixelAt(int x, int y, Rgb c);
	void writePng(const fs::path& png);

private:
	Magick::Image img;

	static inline double toMagickChannel(uint8_t chan);
};

#endif //COURSE_PROJECT_IMG_HPP
