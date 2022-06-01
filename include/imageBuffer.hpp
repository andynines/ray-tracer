#ifndef COURSE_PROJECT_IMAGEBUFFER_HPP
#define COURSE_PROJECT_IMAGEBUFFER_HPP

#include "math.hpp"
#include "stdFilesystem.hpp"

#include <ImageMagick-6/Magick++.h>

#include <vector>

class ImgBuf {
public:
	static ImgBuf from(const fs::path& file) {
		using Magick::Quantum;
		static constexpr auto maxRgb = static_cast<double>(MaxRGB);
		Magick::Image img;
		img.read(file);
		int width = static_cast<int>(img.size().width());
		int height = static_cast<int>(img.size().height());
		ImgBuf buf(width, height);
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Magick::Color c = img.pixelColor(width - x - 1, height - y - 1);
				buf.at(x, y) = Rgb(c.redQuantum() / maxRgb, c.greenQuantum() / maxRgb, c.blueQuantum() / maxRgb);
			}
		}
		return buf;
	}

	explicit ImgBuf(int width, int height) : width(width), height(height), buf(width, std::vector<Rgb>(height, nullRgb)) {}

	Rgb& at(int x, int y) { return buf[x][y]; }
	[[nodiscard]] const Rgb& at(int x, int y) const { return buf[x][y]; }
	[[nodiscard]] int getWidth() const { return width; }
	[[nodiscard]] int getHeight() const { return height; }

private:
	int width, height;
	std::vector<std::vector<Rgb>> buf;
};

#endif //COURSE_PROJECT_IMAGEBUFFER_HPP
