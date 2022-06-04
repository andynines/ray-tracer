#include "bumpSphere.hpp"

BumpSphere::BumpSphere(const fs::path& bumpMap) : heights(ImgBuf::from(bumpMap)) {

}

void BumpSphere::load() {

}

Material BumpSphere::makeMat(const Vec3 &normal) const {
	return {};
}
