#ifndef COURSE_PROJECT_TIMING_HPP
#define COURSE_PROJECT_TIMING_HPP

#include <chrono>
#include <functional>

namespace chrono = std::chrono;

double timeExecutionOf(std::function<void()>&& callback) {
	const auto start = chrono::high_resolution_clock::now();
	callback();
	const auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

#endif //COURSE_PROJECT_TIMING_HPP
