#ifndef COURSE_PROJECT_IMG_HPP
#define COURSE_PROJECT_IMG_HPP

#include "rgb.hpp"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class Img {
public:
	static constexpr int res = 512;
    static constexpr int halfRes = res / 2;

	void addColorAt(int x, int y, const Rgb& c);
	void writePng(const fs::path& png);

private:
    Rgb px[Img::res][Img::res];

	static inline double toMagickChannel(uint8_t chan);
};

#endif //COURSE_PROJECT_IMG_HPP
