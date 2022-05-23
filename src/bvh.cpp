#include "bvh.hpp"
#include "fileTokenReader.hpp"

#include <numeric>

void Bvh::hit(const Ray& ray, Hit& closestHit) const {
	hitBv(ray, closestHit, root);
}

void Bvh::load() {
	FileTokenReader reader(smf);
	int indexOffset = static_cast<int>(vertices.size());
	size_t origNumFaces = faces.size();
	while (reader.hasNext()) {
		switch (reader.readString()[0]) {
			case '#':
				continue;
			case 'v':
				vertices.emplace_back(trans * reader.readVec3());
				break;
			case 'f':
				int i1 = reader.readInt() + indexOffset - 1;
				int i2 = reader.readInt() + indexOffset - 1;
				int i3 = reader.readInt() + indexOffset - 1;
				faces.emplace_back(i1, i2, i3);
		}
	}
	mats.insert(mats.end(), faces.size() - origNumFaces, std::make_shared<Material>(mat));
	trans.setIdentity();
	mat = Material();
}

void Bvh::setNextSmf(const fs::path& smf) {
	this->smf = smf;
}

void Bvh::loadFinal() {
	computeNormals();

	centroids.reserve(faces.size());
	std::transform(faces.begin(), faces.end(), std::back_inserter(centroids), [&](const IndexTriple& it) {
		return (vertices[it[0]] + vertices[it[1]] + vertices[it[2]]) / 3;
	});

	std::vector<int> faceIndices(faces.size());
	std::iota(faceIndices.begin(), faceIndices.end(), 0);

	fillBv(root, faceIndices.begin(), faceIndices.end(), 0);
}

void Bvh::hitBv(const Ray& ray, Hit& closestHit, const NodePtr& bv) const {
	if (!ray.hitsAabb(bv->aabbMin, bv->aabbMax)) return;
	if (bv->low == nullptr) {
		hitBvFaces(ray, closestHit, bv);
		return;
	}
	hitBv(ray, closestHit, bv->low);
	hitBv(ray, closestHit, bv->high);
}

void Bvh::hitBvFaces(const Ray& ray, Hit& closestHit, const NodePtr& bv) const {
	for (int fi : bv->faceIndices) {
		const IndexTriple& it = faces[fi];
		const Vec3& v0 = vertices[it[0]];
		const Vec3& v1 = vertices[it[1]];
		const Vec3& v2 = vertices[it[2]];

		const double detA = det33(
				v0[0] - v1[0], v0[0] - v2[0], ray.dir[0],
				v0[1] - v1[1], v0[1] - v2[1], ray.dir[1],
				v0[2] - v1[2], v0[2] - v2[2], ray.dir[2]
		);
		const double beta = det33(
				v0[0] - ray.origin[0], v0[0] - v2[0], ray.dir[0],
				v0[1] - ray.origin[1], v0[1] - v2[1], ray.dir[1],
				v0[2] - ray.origin[2], v0[2] - v2[2], ray.dir[2]
		) / detA;
		if (beta < 0.0) continue;

		const double gamma = det33(
				v0[0] - v1[0], v0[0] - ray.origin[0], ray.dir[0],
				v0[1] - v1[1], v0[1] - ray.origin[1], ray.dir[1],
				v0[2] - v1[2], v0[2] - ray.origin[2], ray.dir[2]
		) / detA;
		if (gamma < 0.0 || beta + gamma > 1.0) continue;

		const double t = det33(
				v0[0] - v1[0], v0[0] - v2[0], v0[0] - ray.origin[0],
				v0[1] - v1[1], v0[1] - v2[1], v0[1] - ray.origin[1],
				v0[2] - v1[2], v0[2] - v2[2], v0[2] - ray.origin[2]
		) / detA;
		if (t < 0.0) continue;

		const Vec3 pxNormal = (
				(1.0 - beta - gamma) * vNormals[it[0]] +
				beta * vNormals[it[1]] +
				gamma * vNormals[it[2]]).normalized();
		closestHit.updateIfCloser(t, *mats[fi], pxNormal);
	}
}

void Bvh::fillBv(NodePtr& bv, IndexIterator begin, IndexIterator end, int ax) {
	bv = std::make_shared<BvhNode>();
	setAabb(bv, begin, end);
	size_t rangeWidth = std::distance(begin, end);
	if (rangeWidth <= trisPerBv) {
		bv->faceIndices = std::vector<int>(begin, end);
		return;
	}
	std::sort(begin, end, [&](int fi1, int fi2) { return centroids[fi1][ax] < centroids[fi2][ax]; });
	int newAx = (ax + 1) % 3;
	auto mid = begin + static_cast<int>(rangeWidth / 2);
	fillBv(bv->low, begin, mid, newAx);
	fillBv(bv->high, mid, end, newAx);
}

void Bvh::setAabb(const NodePtr& bv, IndexIterator begin, IndexIterator end) {
	double xmin = maxDouble, ymin = maxDouble, zmin = maxDouble;
	double xmax = minDouble, ymax = minDouble, zmax = minDouble;
	for (auto it = begin; it != end; it++) {
		for (size_t vi : faces[*it]) {
			Vec3 v = vertices[vi];
			xmin = std::min(v[0], xmin);
			ymin = std::min(v[1], ymin);
			zmin = std::min(v[2], zmin);
			xmax = std::max(v[0], xmax);
			ymax = std::max(v[1], ymax);
			zmax = std::max(v[2], zmax);
		}
	}
	bv->aabbMin = Vec3(xmin, ymin, zmin);
	bv->aabbMax = Vec3(xmax, ymax, zmax);
}

void Bvh::computeNormals() {
	std::vector<Vec3> fNormals;
	fNormals.reserve(faces.size());
	for (const IndexTriple& it : faces) {
		Vec3 v0 = vertices[it[0]];
		Vec3 v1 = vertices[it[1]];
		Vec3 v2 = vertices[it[2]];
		Vec3 n = ((v1 - v0).cross(v2 - v0)).normalized();
		fNormals.emplace_back(n);
	}
	for (size_t vi = 0; vi < vertices.size(); vi++) {
		Vec3 vNormal = zero;
		for (size_t fi = 0; fi < faces.size(); fi++) {
			const IndexTriple& it = faces[fi];
			if (vi == it[0] || vi == it[1] || vi == it[2]) {
				vNormal += fNormals[fi];
			}
		}
		vNormals.emplace_back(vNormal.normalized());
	}
}

double Bvh::det33(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
	return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
}
