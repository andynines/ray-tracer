#include "image.hpp"

Img::Img() : img(Magick::Geometry(res, res), Magick::ColorRGB(0, 0, 0)) {
	img.magick("png");
}

void Img::setColorAt(int x, int y, const Rgb& c) {
	//std::lock_guard<std::mutex> lk(imgLk);
	img.pixelColor(x, y, Magick::ColorRGB(
			std::min(c[0], 1.0),
			std::min(c[1], 1.0),
			std::min(c[2], 1.0)
	));
}

void Img::writePng(const fs::path& png) {
	img.write(png);
}
