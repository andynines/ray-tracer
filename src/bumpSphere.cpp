#include "bumpSphere.hpp"

BumpSphere::BumpSphere(const fs::path& bumpMap) : heights(ImgBuf::from(bumpMap)) {

}
