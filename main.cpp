#include "timing.hpp"
#include "htmlBuilder.hpp"
#include "scene.hpp"
#include "smfModel.hpp"
#include "sphere.hpp"

#include <experimental/filesystem>
#include <iostream>
#include <memory>

namespace fs = std::experimental::filesystem;

inline Scene buildScene1() {
    Scene scene(Vec3(0, 0, 0), Vec3(1, 0, 0));
    
    std::shared_ptr<Sphere> ls = std::make_shared<Sphere>();
    ls->translate(Vec3(3, 0, -1));
    ls->scale(0.4);
    ls->paint(Rgb(128, 0, 255));
    scene.addObj(ls);
    
    std::shared_ptr<SmfModel> rabbit = std::make_shared<SmfModel>("smf/bunny200.smf");
    rabbit->translate(Vec3(4, 0, 0));
    rabbit->load();
    rabbit->paint(Rgb(0, 255, 128));
    scene.addObj(rabbit);
    
    std::shared_ptr<Sphere> rs = std::make_shared<Sphere>();
    rs->translate(Vec3(3, 0, 1));
    rs->scale(0.4);
    rs->paint(Rgb(255, 128, 0));
    scene.addObj(rs);
    
    return scene;
}

int main() {
	Scene scene = buildScene1();
    
    Img img;
    const double renderTime = timeExecutionOf([&] {
        img = scene.render();
    });
    const fs::path png = "img1.png";
    img.writePng(png);
    
    HtmlBuilder htmlBuilder;
    htmlBuilder.addHeader("Assignment 1");
    htmlBuilder.addImg(png);
    htmlBuilder.addP("Render time: " + std::to_string(renderTime / 1e6) + " sec");
    htmlBuilder.write("Assignment 1", "index.html");

	return 0;
}
