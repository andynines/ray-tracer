#include "image.hpp"

#include <ImageMagick-6/Magick++.h>

Img::Img() {
	px = new Rgb*[calcRes];
	for (int i = 0; i < calcRes; i++)
		px[i] = new Rgb[calcRes];
}

Img::~Img() {
	for (int i = 0; i < calcRes; i++)
		delete px[i];
	delete px;
}

void Img::setColorAt(int x, int y, const Rgb& c) {
    px[x][y] = c;
}

void Img::writePng(const fs::path& png) {
    Magick::Image img(Magick::Geometry(targetRes, targetRes), Magick::ColorRGB(0, 0, 0));
    img.magick("png");
    for (int x = 0; x < Img::targetRes; x++) {
        for (int y = 0; y < Img::targetRes; y++) {
			int i = 2 * x; // TODO: Don't assume targetRes is half of calcRes
			int j = 2 * y;
            Rgb c = (px[i][j] + px[i+1][j] + px[i][j+1] + px[i+1][j+1]) / 4;
            img.pixelColor(x, y, Magick::ColorRGB(
					std::min(c[0], 1.0),
					std::min(c[1], 1.0),
					std::min(c[2], 1.0)
					));
        }
    }
	img.write(png);
}
