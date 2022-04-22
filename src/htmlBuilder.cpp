#include "htmlBuilder.hpp"
#include "image.hpp"

#include <fstream>

void HtmlBuilder::addHeader(const std::string& s) {
    addElement("h1", s);
}

void HtmlBuilder::addHr() {
    ss << "<hr>" << std::endl;
}

void HtmlBuilder::addPre(const std::string& s) {
    addElement("pre", s);
}

void HtmlBuilder::addImg(const fs::path& img) {
    ss << "<img src='" << img.string() << "' alt='scene' width='" << Img::res << "' height='" << Img::res << "'>" << std::endl;
}

void HtmlBuilder::addP(const std::string& s) {
    addElement("p", s);
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

void HtmlBuilder::addElement(const std::string& element, const std::string& innerHtml) {
    ss << "<" << element << ">" << innerHtml << "</" << element << ">" << std::endl;
}
