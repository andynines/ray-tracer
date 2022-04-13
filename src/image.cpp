#include "image.hpp"
#include "rgb.hpp"

Img::Img() : img(Magick::Geometry(res, res), Magick::ColorRGB(0, 0, 0)) {
	img.magick("png");
}

void Img::colorPixelAt(int x, int y, Rgb c) {
	img.pixelColor(x, y, Magick::ColorRGB(toMagickChannel(c.r), toMagickChannel(c.g), toMagickChannel(c.b)));
}

void Img::writePng(const fs::path& png) {
	img.write(png);
}

double Img::toMagickChannel(uint8_t chan) {
	return static_cast<double>(chan) / 255.0;
}
