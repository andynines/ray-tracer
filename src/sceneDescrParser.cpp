#include "fileTokenReader.hpp"
#include "sceneDescrParser.hpp"
#include "smfModel.hpp"
#include "sphere.hpp"

#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>

SceneDescrParser::SceneDescrParser(const fs::path& descr) : descr(descr), reader(descr), currentObj(nullptr) {
    defineCommands();
}

Scene SceneDescrParser::parse() {
    while (reader.hasNext()) {
        std::string command(reader.readString());
        if (command == commentDelimiter) {
            consumeComment();
        } else {
            lowercase(command);
            commands[command]();
        }
    }
    loadCurrentObj();
    return scene;
}

std::string SceneDescrParser::getRawDescription() const {
    std::ifstream ifs(descr);
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

void SceneDescrParser::defineCommands() {
    commands["camera"] = [&] {
        Vec3 camPos = reader.readVec3();
        Vec3 camDir = reader.readVec3();
        scene.setCam(camPos, camDir);
    };
    commands["sphere"] = [&] {
        loadCurrentObj();
        currentObj = std::make_shared<Sphere>();
    };
    commands["smf"] = [&] {
        loadCurrentObj();
        currentObj = std::make_shared<SmfModel>(reader.readString());
    };
    commands["translate"] = [&] {
        currentObj->translate(reader.readVec3());
    };
    commands["rotate"] = [&] {
        double ang = reader.readFloat();
        Vec3 axis = reader.readVec3();
        currentObj->rotate(ang, axis);
    };
    commands["scale"] = [&] {
        currentObj->scale(reader.readFloat());
    };
    commands["color"] = [&] {
        currentObj->color(reader.readRgb());
    };
    commands["material"] = [&] {
        double ka = reader.readFloat();
        double ks = reader.readFloat();
        double kd = reader.readFloat();
        currentObj->setMaterial(ka, ks, kd);
    };
    commands["shiny"] = [&] {
        currentObj->setShiny(reader.readFloat());
    };
    commands["pointlight"] = [&] {
        Vec3 pos = reader.readVec3();
        Rgb color = reader.readRgb();
        scene.addPointLight(PointLight(pos, color));
    };
}

void SceneDescrParser::consumeComment() {
    while (reader.readString() != commentDelimiter)
        ;
}

void SceneDescrParser::loadCurrentObj() {
    if (currentObj != nullptr) {
        currentObj->load();
        scene.addObj(currentObj);
    }
}

void SceneDescrParser::lowercase(std::string& s) const {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
}
