#ifndef COURSE_PROJECT_SMFMODEL_HPP
#define COURSE_PROJECT_SMFMODEL_HPP

#include "sceneObject.hpp"
#include "rgb.hpp"

#include <experimental/filesystem>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

class SmfModel : public SceneObj {
public:
	SmfModel(const fs::path& smf);
    
    void load();
    Rgb hit(const Ray& ray) const override;

private:
    fs::path smf;
	std::vector<Vec3> vertices;
	std::vector<IndexTriple> indices;
    std::vector<Vec3> normals;
    
    void loadGeometry();
    void computeNormals();
    inline bool hitsTri(const Ray& ray, const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& n) const;
    inline double det33(double a, double b, double c, double d, double e, double f, double g, double h, double i) const;
    std::vector<std::string> tokenize(const std::string& line);
};

#endif //COURSE_PROJECT_SMFMODEL_HPP
