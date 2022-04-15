#include "image.hpp"
#include "rgb.hpp"

#include <ImageMagick-6/Magick++.h>

void Img::addColorAt(int x, int y, const Rgb& c) {
    px[x][y] += c;
}

void Img::writePng(const fs::path& png) {
    Magick::Image img(Magick::Geometry(res, res), Magick::ColorRGB(0, 0, 0));
    img.magick("png");
    for (int x = 0; x < Img::res; x++) {
        for (int y = 0; y < Img::res; y++) {
            const Rgb& c = px[x][y];
            img.pixelColor(x, y, Magick::ColorRGB(toMagickChannel(c.r), toMagickChannel(c.g), toMagickChannel(c.b)));
        }
    }
	img.write(png);
}

double Img::toMagickChannel(uint8_t chan) {
	return static_cast<double>(chan) / 255.0;
}
