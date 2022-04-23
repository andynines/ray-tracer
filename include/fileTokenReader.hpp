#ifndef COURSE_PROJECT_FILETOKENREADER_HPP
#define COURSE_PROJECT_FILETOKENREADER_HPP

#include "math.hpp"
#include "stdFilesystem.hpp"

#include <fstream>
#include <functional>
#include <string>

class FileTokenReader {
public:
    explicit FileTokenReader(const fs::path& file) : ifs(file) {}
    
    bool hasNext() const { return !ifs.eof(); }
    int readInt() { return read<int>(); }
    double readFloat() { return read<double>(); }
	std::string readString() { return read<std::string>(); }

	Vec3 readVec3() {
        double x = readFloat();
        double y = readFloat();
        double z = readFloat();
        return Vec3{x, y, z};
    }

private:
    std::ifstream ifs;

    template <typename T>
    inline T read() {
        T result;
        ifs >> result;
        return result;
    }
};

#endif //COURSE_PROJECT_FILETOKENREADER_HPP
