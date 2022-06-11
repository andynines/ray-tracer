#ifndef COURSE_PROJECT_IMG_HPP
#define COURSE_PROJECT_IMG_HPP

#include "stdFilesystem.hpp"
#include "threadSafeImageBuffer.hpp"

class Img {
public:
	static constexpr int res = 1024;

	Img();

	void setColorAt(int x, int y, const Rgb& c);
	void writePng(const fs::path& png);

private:
	ThreadSafeImgBuf buf;
};

#endif //COURSE_PROJECT_IMG_HPP
