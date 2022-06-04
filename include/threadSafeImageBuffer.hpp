#ifndef COURSE_PROJECT_THREADSAFEIMAGEBUFFER_HPP
#define COURSE_PROJECT_THREADSAFEIMAGEBUFFER_HPP

#include "imageBuffer.hpp"

#include <mutex>
#include <vector>

class ThreadSafeImgBuf {
public:
	ThreadSafeImgBuf(int width, int height) : imgBuf(width, height), xLocks(imgBuf.getWidth()) {}

	Rgb& at(int x, int y) {
		std::lock_guard<std::mutex> lk(xLocks[x]);
		return imgBuf.at(x, y);
	}

private:
	ImgBuf imgBuf;
	std::vector<std::mutex> xLocks;
};

#endif //COURSE_PROJECT_THREADSAFEIMAGEBUFFER_HPP
