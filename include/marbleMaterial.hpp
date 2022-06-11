#ifndef COURSE_PROJECT_MARBLEMATERIAL_HPP
#define COURSE_PROJECT_MARBLEMATERIAL_HPP

#include "marbleSampler.hpp"
#include "material.hpp"

struct MarbleMaterial : public Material {
	MarbleSampler marble;

	[[nodiscard]] Rgb calcDiffuse(const Vec3& pos, const Vec3& normal) const override {
		static constexpr double scale = Img::res;
		static Vec3 shift{Img::res / 2.0, Img::res / 2.0, Img::res / 2.0};
		Vec3 samplePos = scale * (pos + shift).cwiseAbs();
		Rgb sample = marble.sample(samplePos[0], samplePos[1], samplePos[2]);
		sample = sample.cwiseMax(ka * diffuse);
		return Material::calcDiffuse(pos, normal).cwiseProduct(sample);
	}
};

#endif //COURSE_PROJECT_MARBLEMATERIAL_HPP
