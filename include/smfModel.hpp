#ifndef COURSE_PROJECT_SMFMODEL_HPP
#define COURSE_PROJECT_SMFMODEL_HPP

#include "pointLight.hpp"
#include "sceneObject.hpp"
#include "stdFilesystem.hpp"

#include <string>
#include <vector>

class SmfModel : public SceneObj {
public:
	explicit SmfModel(fs::path smf);
    
    void hit(const Ray& ray, Hit& closestHit) const override;
	[[nodiscard]] bool hitsAabb(const Ray& ray) const override;
    void load() override;

private:
    fs::path smf;
	std::vector<Vec3> vertices, vNormals;
	std::vector<IndexTriple> indices;
	Vec3 aabbMin, aabbMax;

	static inline double det33(double a, double b, double c, double d, double e, double f, double g, double h, double i);

    void loadGeometry();
    void computeNormals();
};

#endif //COURSE_PROJECT_SMFMODEL_HPP
