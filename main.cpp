#include "fileTokenReader.hpp"
#include "htmlBuilder.hpp"
#include "scene.hpp"
#include "sceneBuilder.hpp"
#include "smfModel.hpp"
#include "sphere.hpp"
#include "timing.hpp"

#include <experimental/filesystem>
#include <iostream>
#include <memory>

namespace fs = std::experimental::filesystem;

// TODO: BIG THINGS
// 3. Handle depth properly

int main(int argc, char* argv[]) {
	SceneBuilder sceneBuilder(argv[1]);
    Scene scene = sceneBuilder.build();
    
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
