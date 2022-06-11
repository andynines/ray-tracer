#include "marbleSampler.hpp"
#include "math.hpp"

#include <random>

MarbleSampler::MarbleSampler() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0, 1);
	for (auto& z : noise)
		for (auto& y : z)
			for (double& x : y)
				x = dist(gen);
}

Rgb MarbleSampler::sample(double x, double y, double z) const {
	static constexpr double xPeriod = 1, yPeriod = 0, turbPower = 5;
	double fxy = x * xPeriod / width + y * yPeriod / height + turbPower * calcTurbulence(x, y, z) / 256.0;
	double sine = std::fabs(std::sin(fxy * pi));
	return {sine, sine, sine};
}

double MarbleSampler::smooth(double x, double y, double z) const {
	double fractX = x - static_cast<int>(x);
	double fractY = y - static_cast<int>(y);
	double fractZ = z - static_cast<int>(z);

	int x1 = (static_cast<int>(x) + width) % width;
	int y1 = (static_cast<int>(y) + height) % height;
	int z1 = (static_cast<int>(z) + depth) % depth;

	int x2 = (x1 + width - 1) % width;
	int y2 = (y1 + height - 1) % height;
	int z2 = (z1 + depth - 1) % depth;

	double value = 0.0;
	value += fractX * fractY * fractZ * noise[z1][y1][x1];
	value += fractX * (1 - fractY) * fractZ * noise[z1][y2][x1];
	value += (1 - fractX) * fractY * fractZ * noise[z1][y1][x2];
	value += (1 - fractX) * (1 - fractY) * fractZ * noise[z1][y2][x2];

	value += fractX * fractY * (1 - fractZ) * noise[z2][y1][x1];
	value += fractX * (1 - fractY) * (1 - fractZ) * noise[z2][y2][x1];
	value += (1 - fractX) * fractY * (1 - fractZ) * noise[z2][y1][x2];
	value += (1 - fractX) * (1 - fractY) * (1 - fractZ) * noise[z2][y2][x2];

	return value;
}

double MarbleSampler::calcTurbulence(double x, double y, double z) const {
	static constexpr double initialSize = 8.0;
	double value = 0.0, size = initialSize;
	while (size >= 1) {
		value += smooth(x / size, y / size, z / size) * size;
		size /= 2.0;
	}
	return 128.0 * value / initialSize;
}
