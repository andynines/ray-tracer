#include "timing.hpp"
#include "htmlBuilder.hpp"
#include "scene.hpp"
#include "smfModel.hpp"
#include "sphere.hpp"

#include <experimental/filesystem>
#include <iostream>
#include <memory>

namespace fs = std::experimental::filesystem;

// TODO: BIG THINGS
// 1. Load normals correctly (consider making a SDL)
// 2. See assignment page for final verdict on what interpretation of the Phong model we're using
// 3. Handle depth properly

inline Scene buildScene1() {
    Scene scene(Vec3(0, 0, 0), Vec3(1, 0, 0));
    
    std::shared_ptr<Sphere> ls = std::make_shared<Sphere>();
    ls->translate(Vec3(3, 0, -1));
    ls->scale(0.8);
    ls->style(Rgb(0.5, 0, 1), Rgb(0.5, 0.5, 0.5), Rgb(0.5, 0, 1), 32);
    scene.addObj(ls);
    
    std::shared_ptr<SmfModel> rabbit = std::make_shared<SmfModel>("smf/cow.smf");
    rabbit->rotate(90, up);
    rabbit->translate(Vec3(4, 0, 0));
    rabbit->load();
    rabbit->style(Rgb(0, 1, 0.5), Rgb(0.5, 0.5, 0.5), Rgb(0, 1, 0.5), 32);
    scene.addObj(rabbit);
    
    std::shared_ptr<Sphere> rs = std::make_shared<Sphere>();
    rs->translate(Vec3(3, 0, 1));
    rs->scale(0.4);
    rs->style(Rgb(1, 0.5, 0), Rgb(0.5, 0.5, 0.5), Rgb(1, 0.5, 0), 32);
    scene.addObj(rs);
    
    scene.addPointLight(PointLight(Vec3(2, 3, 0), Rgb(1.0, 1.0, 1.0)));
    
    return scene;
}

int main() {
	Scene scene = buildScene1();
    
    Img img;
    const double renderTime = timeExecutionOf([&] { scene.renderTo(img); });
    const fs::path png = "img2.png";
    img.writePng(png);
    
    HtmlBuilder htmlBuilder;
    htmlBuilder.addHeader("Assignment 1");
    htmlBuilder.addImg(png);
    htmlBuilder.addP("Render time: " + std::to_string(renderTime / 1e6) + " sec");
    htmlBuilder.write("Assignment 1", "index.html");

	return 0;
}
