#ifndef COURSE_PROJECT_RENDERER_HPP
#define COURSE_PROJECT_RENDERER_HPP

#include "image.hpp"
#include "scene.hpp"

class Renderer {
public:
	explicit Renderer(const Scene& scene);

	void render(Img& img);

private:
	static inline bool isWithinTolerance(const Rgb& a, const Rgb& b, const Rgb& c, const Rgb& d);

	static constexpr double fov = toRad(56);
	static constexpr int supersampleScale = 4;
	static constexpr int sampleBufRes = supersampleScale * Img::res + 1;
	static constexpr int halfSampleBufRes = sampleBufRes / 2;

	void renderSection(int startX, int numXs, Img& img);
	Rgb averageSubdivisionsAt(int x, int y, int d);
	Rgb fetchOrComputeSample(int x, int y);

	const Scene& scene;
	double pxLength;
	ImgBuf samples;
};

#endif //COURSE_PROJECT_RENDERER_HPP
