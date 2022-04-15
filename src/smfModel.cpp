#include "smfModel.hpp"

#include <fstream>
#include <sstream>

SmfModel::SmfModel(const fs::path& smf) : SceneObj(), smf(smf) {}

void SmfModel::load() {
    loadGeometry();
    computeNormals();
}

Rgb SmfModel::hit(const Ray& ray) const {
    for (int i = 0; i < indices.size(); i++) {
        const Vec3& n = normals[i];
        if (ray.dir.dot(n) > 0.0) continue;
        const IndexTriple it = indices[i];
        const Vec3& v0 = vertices[it[0]];
        const Vec3& v1 = vertices[it[1]];
        const Vec3& v2 = vertices[it[2]];
        if (hitsTri(ray, v0, v1, v2, n)) return color;
    }
    return Rgb();
}

void SmfModel::loadGeometry() {
    vertices.clear();
    indices.clear();
    std::ifstream ifs(smf);
	std::string line;
	while (std::getline(ifs, line)) {
		const std::vector<std::string> tokens = tokenize(line);
		switch (tokens[0][0]) {
			case '#':
				continue;
			case 'v':
                vertices.emplace_back(trans * Vec3(
                    std::stod(tokens[1]),
                    std::stod(tokens[2]),
                    std::stod(tokens[3])));
				break;
			case 'f':
				indices.emplace_back(
						std::stoi(tokens[1]) - 1,
						std::stoi(tokens[2]) - 1,
						std::stoi(tokens[3]) - 1);
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
        Vec3 n = (trans.linear() * (v1 - v0).cross(v2 - v0)).normalized();
        normals.emplace_back(n);
    }
}

bool SmfModel::hitsTri(const Ray& ray, const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& n) const {
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
    if (beta < 0.0) return false;
    const double gamma = det33(
        a[0] - b[0], a[0] - ray.origin[0], ray.dir[0],
        a[1] - b[1], a[1] - ray.origin[1], ray.dir[1],
        a[2] - b[2], a[2] - ray.origin[2], ray.dir[2]
    ) / detA;
    if (gamma < 0.0 || beta + gamma > 1.0) return false;
    const double t = det33(
        a[0] - b[0], a[0] - c[0], a[0] - ray.origin[0],
        a[1] - b[1], a[1] - c[1], a[1] - ray.origin[1],
        a[2] - b[2], a[2] - c[2], a[2] - ray.origin[2]
    ) / detA;
    return t >= 0.0;
}

double SmfModel::det33(double a, double b, double c, double d, double e, double f, double g, double h, double i) const {
    return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
}

std::vector<std::string> SmfModel::tokenize(const std::string& line) {
	std::vector<std::string> tokens;
	std::stringstream ss(line);
	std::string tok;
	while (std::getline(ss, tok, ' ')) {
		tokens.push_back(tok);
	}
	return tokens;
}
