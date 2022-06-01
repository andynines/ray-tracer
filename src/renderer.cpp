#include "renderer.hpp"

#include <thread>

Renderer::Renderer(const Scene& scene) :
	scene(scene),
	pxLength(2 * std::tan(fov * 0.5) / sampleBufRes),
	samples(sampleBufRes, sampleBufRes) {}

void Renderer::render(Img& img) {
	int numThreads = 0; //static_cast<int>(std::thread::hardware_concurrency());
	if (numThreads == 0) {
		renderSection(0, Img::res, img);
		return;
	}

	// TODO: Implement a more robust work distribution method.
	// This one relies on each thread completing their first x before their previous neighbor starts its last x
	int rowsPerThread = Img::res / numThreads;
	std::vector<std::thread> threads;
	threads.reserve(numThreads);
	int i;
	for (i = 0; i < numThreads - 1; i++)
		threads.emplace_back(&Renderer::renderSection, this, i * rowsPerThread, rowsPerThread, std::ref(img));
	threads.emplace_back(&Renderer::renderSection, this, i * rowsPerThread, rowsPerThread + Img::res % numThreads, std::ref(img));
	for (std::thread& t : threads)
		t.join();
}

void Renderer::renderSection(int startX, int numXs, Img& img) {
	int endIndex = startX + numXs;
	for (int x = startX; x < endIndex; x++)
		for (int y = 0; y < Img::res; y++)
			img.setColorAt(x, y, averageSubdivisionsAt(x * supersampleScale, y * supersampleScale, supersampleScale));
}

Rgb Renderer::averageSubdivisionsAt(int x, int y, int d) {
	Rgb rgb0 = fetchOrComputeSample(x, y);
	Rgb rgb1 = fetchOrComputeSample(x + d, y);
	Rgb rgb2 = fetchOrComputeSample(x, y + d);
	Rgb rgb3 = fetchOrComputeSample(x + d, y + d);
	if (d > 1 && !isWithinTolerance(rgb0, rgb1, rgb2, rgb3)) {
		d /= 2;
		return (
			   averageSubdivisionsAt(x, y, d) +
			   averageSubdivisionsAt(x + d, y, d) +
			   averageSubdivisionsAt(x, y + d, d) +
			   averageSubdivisionsAt(x + d, y + d, d)
			   ) / 4;
	}
	return (rgb0 + rgb1 + rgb2 + rgb3) / 4;
}

Rgb Renderer::fetchOrComputeSample(int x, int y) {
	Rgb& sample = samples.at(x, y);
	if (sample != nullRgb) return sample;
	sample = scene.calcPxColor((x - halfSampleBufRes) * pxLength, (halfSampleBufRes - y) * pxLength);
	return sample;
}

bool Renderer::isWithinTolerance(const Rgb& a, const Rgb& b, const Rgb& c, const Rgb& d) {
	static constexpr double tol = 0.05;
	return (a - b).lpNorm<1>() <= tol &&
		   (a - c).lpNorm<1>() <= tol &&
		   (b - d).lpNorm<1>() <= tol &&
		   (c - d).lpNorm<1>() <= tol;
}
