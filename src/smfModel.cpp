#include "fileTokenReader.hpp"
#include "smfModel.hpp"

#include <sstream>
#include <utility>

SmfModel::SmfModel(fs::path smf) : SceneObj(), smf(std::move(smf)) {}

void SmfModel::hit(const Ray& ray, Hit& closestHit) const {
    for (size_t i = 0; i < indices.size(); i++) {
        const Vec3& n = normals[i];
        const IndexTriple it = indices[i];
        const Vec3& v0 = vertices[it[0]];
        const Vec3& v1 = vertices[it[1]];
        const Vec3& v2 = vertices[it[2]];
        const double t = calcTriHit(ray, v0, v1, v2); // TODO: inline me
        if (t < 0.0) continue;
        closestHit.updateIfCloser(t, mat, n);
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
    normals.clear();
    normals.reserve(indices.size());
    for (const IndexTriple& it : indices) {
        Vec3 v0 = vertices[it[0]];
        Vec3 v1 = vertices[it[1]];
        Vec3 v2 = vertices[it[2]];
        Vec3 n = ((v1 - v0).cross(v2 - v0)).normalized();
        normals.emplace_back(n);
    }
}

double SmfModel::calcTriHit(const Ray& ray, const Vec3& a, const Vec3& b, const Vec3& c) {
    const double detA = det33(
        a[0] - b[0], a[0] - c[0], ray.dir[0],
        a[1] - b[1], a[1] - c[1], ray.dir[1],
        a[2] - b[2], a[2] - c[2], ray.dir[2]
    );
    const double beta = det33(
        a[0] - ray.origin[0], a[0] - c[0], ray.dir[0],
        a[1] - ray.origin[1], a[1] - c[1], ray.dir[1],
        a[2] - ray.origin[2], a[2] - c[2], ray.dir[2]
    ) / detA;
    if (beta < 0.0) return Hit::noHit;
    const double gamma = det33(
        a[0] - b[0], a[0] - ray.origin[0], ray.dir[0],
        a[1] - b[1], a[1] - ray.origin[1], ray.dir[1],
        a[2] - b[2], a[2] - ray.origin[2], ray.dir[2]
    ) / detA;
    if (gamma < 0.0 || beta + gamma > 1.0) return Hit::noHit;
    return det33(
        a[0] - b[0], a[0] - c[0], a[0] - ray.origin[0],
        a[1] - b[1], a[1] - c[1], a[1] - ray.origin[1],
        a[2] - b[2], a[2] - c[2], a[2] - ray.origin[2]
    ) / detA;
}

double SmfModel::det33(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
    return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
}
