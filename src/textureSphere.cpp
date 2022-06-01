#include "textureSphere.hpp"

TexSphere::TexSphere(const fs::path& tex) : buf(ImgBuf::from(tex)) {}

void TexSphere::load() {
    Sphere::load();
	invTrans = trans.inverse();
}

Material TexSphere::makeMat(const Vec3& normal) const {
	Vec3 localNormal = (invTrans.linear() * normal).normalized();
	int u = static_cast<int>((std::atan(localNormal[2] / localNormal[0]) / pi + 0.5) * buf.getWidth());
	int v = static_cast<int>((localNormal[1] + 1) / 2 * buf.getHeight());
	Material newMat = mat;
	newMat.diffuse = buf.at(u, v);
	return newMat;
}
