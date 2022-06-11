#ifndef COURSE_PROJECT_TEXTUREMATERIAL_HPP
#define COURSE_PROJECT_TEXTUREMATERIAL_HPP

#include "imageBuffer.hpp"
#include "material.hpp"

struct TexMaterial : public Material {
	ImgBuf buf;

	explicit TexMaterial(const fs::path& tex) : buf(ImgBuf::from(tex)) {}

	[[nodiscard]] Rgb calcDiffuse(const Vec3& pos, const Vec3& normal) const override {
		int u = static_cast<int>((std::atan(normal[2] / normal[0]) / pi + 0.5) * buf.getWidth());
		u = std::min(u, buf.getWidth() - 1);
		int v = static_cast<int>((normal[1] + 1) / 2 * buf.getHeight());
		return buf.at(u, v);
	}
};

#endif //COURSE_PROJECT_TEXTUREMATERIAL_HPP
