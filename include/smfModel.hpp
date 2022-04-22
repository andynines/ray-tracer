#ifndef COURSE_PROJECT_SMFMODEL_HPP
#define COURSE_PROJECT_SMFMODEL_HPP

#include "pointLight.hpp"
#include "rgb.hpp"
#include "sceneObject.hpp"
#include "stdFilesystem.hpp"

#include <string>
#include <vector>

class SmfModel : public SceneObj {
public:
	explicit SmfModel(fs::path smf);
    
    void hit(const Ray& ray, const std::vector<PointLight>& pointLights, Hit& closestHit) const override;
    void load() override;

private:
    fs::path smf;
	std::vector<Vec3> vertices;
	std::vector<IndexTriple> indices;
    std::vector<Vec3> normals;

	static inline double calcTriHit(const Ray& ray, const Vec3& a, const Vec3& b, const Vec3& c);
	static inline double det33(double a, double b, double c, double d, double e, double f, double g, double h, double i);
	static std::vector<std::string> tokenize(const std::string& line);

    void loadGeometry();
    void computeNormals();
};

#endif //COURSE_PROJECT_SMFMODEL_HPP
