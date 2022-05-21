#include "image.hpp"

#include <ImageMagick-6/Magick++.h>

Img::Img() : px(res) {}

void Img::setColorAt(int r, int c, const Rgb& rgb) {
    px.at(r, c) = rgb;
}

void Img::writePng(const fs::path& png) {
    Magick::Image img(Magick::Geometry(res, res), Magick::ColorRGB(0, 0, 0));
    img.magick("png");
    for (int x = 0; x < Img::res; x++) {
        for (int y = 0; y < Img::res; y++) {
			Rgb c = px.at(x, y);
            img.pixelColor(x, y, Magick::ColorRGB(
					std::min(c[0], 1.0),
					std::min(c[1], 1.0),
					std::min(c[2], 1.0)
					));
        }
    }
	img.write(png);
}
