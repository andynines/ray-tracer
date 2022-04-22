#include "image.hpp"
#include "rgb.hpp"

#include <ImageMagick-6/Magick++.h>

void Img::setColorAt(int x, int y, const Rgb& c) {
    px[x][y] = c;
}

void Img::writePng(const fs::path& png) {
    Magick::Image img(Magick::Geometry(res, res), Magick::ColorRGB(0, 0, 0));
    img.magick("png");
    for (int x = 0; x < Img::res; x++) {
        for (int y = 0; y < Img::res; y++) {
            const Rgb& c = px[x][y];
            img.pixelColor(x, y, Magick::ColorRGB(c.r, c.g, c.b));
        }
    }
	img.write(png);
}
