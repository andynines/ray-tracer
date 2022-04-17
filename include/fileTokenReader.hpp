#ifndef COURSE_PROJECT_FILETOKENREADER_HPP
#define COURSE_PROJECT_FILETOKENREADER_HPP

#include "math.hpp"
#include "rgb.hpp"

#include <experimental/filesystem>
#include <fstream>
#include <functional>
#include <string>

namespace fs = std::experimental::filesystem;

class FileTokenReader {
public:
    explicit FileTokenReader(const fs::path& file);
    
    bool hasNext() const;
    int readInt();
    double readFloat();
    Vec3 readVec3();
    Rgb readRgb();
    std::string readString();
    
private:
    std::ifstream ifs;
};

#endif //COURSE_PROJECT_FILETOKENREADER_HPP
