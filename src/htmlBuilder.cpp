#include "htmlBuilder.hpp"
#include "image.hpp"

#include <fstream>

void HtmlBuilder::addHeader(const std::string& s) {
    ss << "<h1>" << s << "</h1>" << std::endl;
}

void HtmlBuilder::addImg(const fs::path& img) {
    ss << "<img src='" << img.string() << "' alt='scene' width='" << Img::res << "' height='" << Img::res << "'>" << std::endl;
}

void HtmlBuilder::addP(const std::string& s) {
    ss << "<p>" << s << "</p>" << std::endl;
}

void HtmlBuilder::write(const std::string& title, const fs::path& path) {
    std::ofstream ofs(path);
    ofs << "<!doctype html>" << std::endl;
    ofs << "<html>" << std::endl;
    ofs << "<head><title>" << title << "</title></head>" << std::endl;
    ofs << "<body>" << std::endl;
    ofs << ss.rdbuf();
    ofs << "</body>" << std::endl;
    ofs << "</html>" << std::endl;
}
