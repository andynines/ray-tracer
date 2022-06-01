#ifndef COURSE_PROJECT_TEXTURESPHERE_HPP
#define COURSE_PROJECT_TEXTURESPHERE_HPP

#include "imageBuffer.hpp"
#include "sphere.hpp"
#include "stdFilesystem.hpp"

class TexSphere : public Sphere {
public:
    explicit TexSphere(const fs::path& tex);

	void load() override;

private:
	[[nodiscard]] Material makeMat(const Vec3& normal) const override;

	ImgBuf buf;
	Transform invTrans;
};

#endif //COURSE_PROJECT_TEXTURESPHERE_HPP
