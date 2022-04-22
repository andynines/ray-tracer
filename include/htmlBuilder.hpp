#ifndef COURSE_PROJECT_HTMLBUILDER_HPP
#define COURSE_PROJECT_HTMLBUILDER_HPP

#include "stdFilesystem.hpp"

#include <sstream>
#include <string>

class HtmlBuilder {
public:
    void addHeader(const std::string& s);
    void addHr();
    void addPre(const std::string& s);
    void addImg(const fs::path& img);
    void addP(const std::string& s);
    void write(const std::string& title, const fs::path& path);
    
private:
    std::stringstream ss;
    
    void addElement(const std::string& element, const std::string& innerHtml);
};

#endif //COURSE_PROJECT_HTMLBUILDER_HPP
