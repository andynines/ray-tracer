#ifndef COURSE_PROJECT_HTMLBUILDER_HPP
#define COURSE_PROJECT_HTMLBUILDER_HPP

#include <experimental/filesystem>
#include <sstream>
#include <string>

namespace fs = std::experimental::filesystem;

class HtmlBuilder {
public:
    void addHeader(const std::string& s);
    void addImg(const fs::path& img);
    void addP(const std::string& s);
    void write(const std::string& title, const fs::path& path);
    
private:
    std::stringstream ss;
};

#endif //COURSE_PROJECT_HTMLBUILDER_HPP
