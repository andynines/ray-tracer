#ifndef COURSE_PROJECT_SCENE_HPP
#define COURSE_PROJECT_SCENE_HPP

#include "image.hpp"
#include "pointLight.hpp"
#include "sceneObject.hpp"

#include <memory>
#include <vector>

class Scene {
public:
    Scene();

    void setCam(const Vec3& camPos, const Vec3& camDir);
    void addObj(const std::shared_ptr<SceneObj>& obj);
    void addPointLight(const PointLight& pl);
    void renderTo(Img& img);
	[[nodiscard]] int getNumRaysCast() const { return numRaysCast; }
    
private:
    static constexpr double fov = toRad(56);
	static constexpr int primaryRayBufRes = Img::res + 1;

	static inline bool isWithinTolerance(const Rgb& a, const Rgb& b, const Rgb& c, const Rgb& d);
	static inline constexpr bool isWhole(double d);

	void becomeWorkerThread(int threadIndex, int stride, Img& img);
	Rgb resolve(double x, double y, double d = 0.5);
	Rgb calcPxColor(double x, double y);
	Rgb cast(const Ray& ray);

    Vec3 camPos, projPlaneCenter, right;
    double pxLength;
    std::vector<std::shared_ptr<SceneObj>> objs;
    std::vector<PointLight> pointLights;
	ImgBuf primaryRayColors;
	int numRaysCast;
};

#endif //COURSE_PROJECT_SCENE_HPP
