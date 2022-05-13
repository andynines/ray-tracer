#ifndef COURSE_PROJECT_SMFMODEL_HPP
#define COURSE_PROJECT_SMFMODEL_HPP

#include "pointLight.hpp"
#include "sceneObject.hpp"
#include "stdFilesystem.hpp"

#include <memory>
#include <string>
#include <vector>

class SmfModel : public SceneObj {
public:
	explicit SmfModel(fs::path smf);

	static void constructBvh();
	static void hitAll(const Ray& ray, Hit& closestHit);

    void hit(const Ray& ray, Hit& closestHit) const override;
    void load() override;

private:
	struct BvhNode {
		Vec3 aabbMin;
		Vec3 aabbMax;
		std::shared_ptr<BvhNode> low;
		std::shared_ptr<BvhNode> high;
		std::vector<int> faceIndices;
	};
	using NodePtr = std::shared_ptr<BvhNode>;
	using IndexIterator = std::vector<int>::iterator;

	static constexpr int trisPerBv = 10;

	static inline std::vector<Vec3> vertices, vNormals, centroids;
	static inline std::vector<IndexTriple> faces;
	static inline std::vector<Material*> mats;
	static inline NodePtr bvh;

    fs::path smf;

	static inline double det33(double a, double b, double c, double d, double e, double f, double g, double h, double i);
	static void computeNormals();
	static void fillBv(NodePtr& bv, IndexIterator begin, IndexIterator end, int ax);
	static void setAabb(const NodePtr& bv, IndexIterator begin, IndexIterator end);
	static void hitBv(const Ray& ray, Hit& closestHit, const NodePtr& bv);
	static void hitBvFaces(const Ray& ray, Hit& closestHit, const NodePtr& bv);
};

#endif //COURSE_PROJECT_SMFMODEL_HPP
