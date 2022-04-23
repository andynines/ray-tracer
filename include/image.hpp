#ifndef COURSE_PROJECT_IMG_HPP
#define COURSE_PROJECT_IMG_HPP

#include "math.hpp"
#include "stdFilesystem.hpp"

#include <array>

class Img {
public:
	static constexpr int res = 512;
    static constexpr int halfRes = res / 2;

	void setColorAt(int x, int y, const Rgb& c);
	void writePng(const fs::path& png);

private:
    std::array<std::array<Rgb, Img::res>, Img::res> px;
};

#endif //COURSE_PROJECT_IMG_HPP
