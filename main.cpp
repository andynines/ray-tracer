#include "htmlBuilder.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "sceneDescriptionParser.hpp"
#include "stdFilesystem.hpp"
#include "timing.hpp"

#include "marbleSampler.hpp" // TODO: REMOVE ME

#include <iostream>

#define PAGE_TITLE ("Assignment 7")

inline void generateScenesWebpage(const std::vector<fs::path>& sceneDescrs) {
    HtmlBuilder htmlBuilder;
    htmlBuilder.addHeader(PAGE_TITLE);

    for (const fs::path& descr : sceneDescrs) {
        SceneDescrParser sceneDescrParser(descr);
        Scene scene = sceneDescrParser.parse();
		Renderer renderer(scene);
        Img img;
        double renderTime = timeExecutionOf([&] { renderer.render(img); });

        fs::path png = descr.stem();
        png.replace_extension("png");
        img.writePng(png);
        
        htmlBuilder.addHr();
        htmlBuilder.addPre(sceneDescrParser.getRawDescription());
        htmlBuilder.addImg(png);
        htmlBuilder.addP("Rendered in " + std::to_string(renderTime) + " sec");
    }
    htmlBuilder.write(PAGE_TITLE, "index.html");
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " scene-description-1 scene-description-2 ... scene-description-n" << std::endl;
        return 0;
    }
    
    std::vector<fs::path> sceneDescrs(argv + 1, argv + argc);
    generateScenesWebpage(sceneDescrs);

	return 0;
}
