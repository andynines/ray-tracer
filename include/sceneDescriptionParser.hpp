#ifndef COURSE_PROJECT_SCENEDESCRIPTIONPARSER_HPP
#define COURSE_PROJECT_SCENEDESCRIPTIONPARSER_HPP

#include "fileTokenReader.hpp"
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
    static inline const std::string commentDelimiter = "#";

    fs::path descr;
    Scene scene;
    FileTokenReader reader;
    std::unordered_map<std::string, std::function<void()>> commands;
    std::shared_ptr<SceneObj> currentObj;

    static inline void lowercase(std::string& s);

    void defineCommands();
    void consumeComment();
    void loadCurrentObj();
};

#endif //COURSE_PROJECT_SCENEDESCRIPTIONPARSER_HPP
