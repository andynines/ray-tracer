#include "fileTokenReader.hpp"
#include "htmlBuilder.hpp"
#include "scene.hpp"
#include "sceneDescrParser.hpp"
#include "stdFilesystem.hpp"
#include "timing.hpp"

#include <iostream>

#define PAGE_TITLE ("Assignment 4")

inline void generateScenesWebpage(const std::vector<fs::path>& sceneDescrs) {
    HtmlBuilder htmlBuilder;
    htmlBuilder.addHeader(PAGE_TITLE);
    
    for (const fs::path& descr : sceneDescrs) {
        SceneDescrParser sceneDescrParser(descr);
        Scene scene = sceneDescrParser.parse();
        Img img;
        const double renderTime = timeExecutionOf([&] { scene.renderTo(img); });
        
        fs::path png = descr.stem();
        png.replace_extension("png");
        img.writePng(png);
        
        htmlBuilder.addHr();
        htmlBuilder.addPre(sceneDescrParser.getRawDescription());
        htmlBuilder.addImg(png);
        htmlBuilder.addP("Render time: " + std::to_string(renderTime) + " sec");
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
