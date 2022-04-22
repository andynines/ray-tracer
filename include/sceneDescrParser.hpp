#ifndef COURSE_PROJECT_SCENEDESCRPARSER_HPP
#define COURSE_PROJECT_SCENEDESCRPARSER_HPP

#include "scene.hpp"
#include "sceneObject.hpp"
#include "stdFilesystem.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

class SceneDescrParser {
public:
    explicit SceneDescrParser(const fs::path& descr);
    
    Scene parse();
    std::string getRawDescription() const;
    
private:
    inline static const std::string commentDelimiter = "#";

    fs::path descr;
    Scene scene;
    FileTokenReader reader;
    std::unordered_map<std::string, std::function<void()>> commands;
    std::shared_ptr<SceneObj> currentObj;
    
    void defineCommands();
    void consumeComment();
    void loadCurrentObj();
    inline void lowercase(std::string& s) const;
};

#endif //COURSE_PROJECT_SCENEDESCRPARSER_HPP
