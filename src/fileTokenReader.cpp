#include "fileTokenReader.hpp"

FileTokenReader::FileTokenReader(const fs::path& file) : ifs(file) {}

bool FileTokenReader::hasNext() const {
    return !ifs.eof();
}

int FileTokenReader::readInt() {
    int i;
    ifs >> i;
    return i;
}

double FileTokenReader::readFloat() {
    double d;
    ifs >> d;
    return d;
}

Vec3 FileTokenReader::readVec3() {
    double x = readFloat();
    double y = readFloat();
    double z = readFloat();
    return Vec3(x, y, z);
}

Rgb FileTokenReader::readRgb() {
    double r = readFloat();
    double g = readFloat();
    double b = readFloat();
    return Rgb(r, g, b);
}

std::string FileTokenReader::readString() {
    std::string s;
    ifs >> s;
    return s;
}
