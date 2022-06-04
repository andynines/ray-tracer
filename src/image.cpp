#include "image.hpp"

Img::Img() : buf(res, res) {}

void Img::setColorAt(int x, int y, const Rgb& c) {
	buf.at(x, y) = Rgb(std::min(c[0], 1.0),
					   std::min(c[1], 1.0),
					   std::min(c[2], 1.0));
}

void Img::writePng(const fs::path& png) {
	Magick::Image img(Magick::Geometry(res, res), Magick::ColorRGB(0, 0, 0));
	img.magick("png");
	for (int x = 0; x < res; x++) {
		for (int y = 0; y < res; y++) {
			Rgb c = buf.at(x, y);
			img.pixelColor(x, y, Magick::ColorRGB(c[0], c[1], c[2]));
		}
	}
	img.write(png);
}
