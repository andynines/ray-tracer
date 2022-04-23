#ifndef COURSE_PROJECT_IMG_HPP
#define COURSE_PROJECT_IMG_HPP

#include "math.hpp"
#include "stdFilesystem.hpp"

#include <array>

class Img {
public:
	static constexpr int calcRes = 1024;
    static constexpr int targetRes = calcRes / 2;

	Img();
	~Img();

	void setColorAt(int x, int y, const Rgb& c);
	void writePng(const fs::path& png);

private:
    Rgb** px;
};

#endif //COURSE_PROJECT_IMG_HPP
