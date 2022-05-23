#ifndef COURSE_PROJECT_BVH_HPP
#define COURSE_PROJECT_BVH_HPP

#include "material.hpp"
#include "math.hpp"
#include "sceneObject.hpp"
#include "stdFilesystem.hpp"

#include <memory>

class Bvh : public SceneObj {
public:
	void hit(const Ray& ray, Hit& closestHit) const override;
	void load() override;

	void setNextSmf(const fs::path& smf);
	void loadFinal();

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

	fs::path smf;
	std::vector<Vec3> vertices, vNormals, centroids;
	std::vector<IndexTriple> faces;
	std::vector<std::shared_ptr<Material>> mats;
	NodePtr root;

	static inline double det33(double a, double b, double c, double d, double e, double f, double g, double h, double i);

	void computeNormals();
	void fillBv(NodePtr& bv, IndexIterator begin, IndexIterator end, int ax);
	void setAabb(const NodePtr& bv, IndexIterator begin, IndexIterator end);
	void hitBv(const Ray& ray, Hit& closestHit, const NodePtr& bv) const;
	void hitBvFaces(const Ray& ray, Hit& closestHit, const NodePtr& bv) const;
};

#endif //COURSE_PROJECT_BVH_HPP
