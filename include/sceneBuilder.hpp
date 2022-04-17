#ifndef COURSE_PROJECT_SCENEBUILDER_HPP
#define COURSE_PROJECT_SCENEBUILDER_HPP

#include "scene.hpp"
#include "sceneObject.hpp"

#include <experimental/filesystem>
#include <functional>
#include <memory>
#include <unordered_map>

namespace fs = std::experimental::filesystem;

class SceneBuilder {
public:
    explicit SceneBuilder(const fs::path& descr);
    
    Scene build();
    
private:
    Scene scene;
    FileTokenReader reader;
    std::unordered_map<std::string, std::function<void()>> commands;
    std::shared_ptr<SceneObj> currentObj;
    
    void defineCommands();
    void loadCurrentObj();
    inline void lowercase(std::string& s) const;
};

#endif //COURSE_PROJECT_SCENEBUILDER_HPP
