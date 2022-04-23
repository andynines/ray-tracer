#include "fileTokenReader.hpp"
#include "smfModel.hpp"

#include <utility>

SmfModel::SmfModel(fs::path smf) : SceneObj(), smf(std::move(smf)) {}

void SmfModel::hit(const Ray& ray, Hit& closestHit) const {
    for (const IndexTriple& it : indices) {
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
        closestHit.updateIfCloser(t, mat, pxNormal);
    }
}

void SmfModel::load() {
    loadGeometry();
    computeNormals();
}

void SmfModel::loadGeometry() {
    vertices.clear();
    indices.clear();
    FileTokenReader reader(smf);
    while (reader.hasNext()) {
        switch (reader.readString()[0]) {
            case '#':
                continue;
            case 'v':
                vertices.emplace_back(trans * reader.readVec3());
                break;
            case 'f':
                int i1 = reader.readInt() - 1;
                int i2 = reader.readInt() - 1;
                int i3 = reader.readInt() - 1;
                indices.emplace_back(i1, i2, i3);
        }
    }
}

void SmfModel::computeNormals() {
    std::vector<Vec3> fNormals;
    fNormals.reserve(indices.size());
    for (const IndexTriple& it : indices) {
        Vec3 v0 = vertices[it[0]];
        Vec3 v1 = vertices[it[1]];
        Vec3 v2 = vertices[it[2]];
        Vec3 n = ((v1 - v0).cross(v2 - v0)).normalized();
        fNormals.emplace_back(n);
    }
	vNormals.clear();
	vNormals.reserve(vertices.size());
	for (size_t vi = 0; vi < vertices.size(); vi++) {
		Vec3 vNormal = zero;
		for (size_t fi = 0; fi < indices.size(); fi++) {
			const IndexTriple& it = indices[fi];
			if (vi == it[0] || vi == it[1] || vi == it[2]) {
				vNormal += fNormals[fi];
			}
		}
		vNormals.emplace_back(vNormal.normalized());
	}
}

double SmfModel::det33(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
    return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
}
