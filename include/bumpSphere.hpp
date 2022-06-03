#ifndef COURSE_PROJECT_BUMPSPHERE_HPP
#define COURSE_PROJECT_BUMPSPHERE_HPP

#include "imageBuffer.hpp"
#include "sphere.hpp"
#include "stdFilesystem.hpp"

class BumpSphere : public Sphere {
public:
	explicit BumpSphere(const fs::path& bumpMap);

	void load() override;

private:
	[[nodiscard]] Material makeMat(const Vec3& normal) const override;

	ImgBuf heights;
};

#endif //COURSE_PROJECT_BUMPSPHERE_HPP
