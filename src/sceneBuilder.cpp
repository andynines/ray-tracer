#include "fileTokenReader.hpp"
#include "sceneBuilder.hpp"
#include "smfModel.hpp"
#include "sphere.hpp"

#include <functional>
#include <iostream> // TODO: remove me
#include <string>
#include <unordered_map>

SceneBuilder::SceneBuilder(const fs::path& descr) : reader(descr), currentObj(nullptr) {
    defineCommands();
}

Scene SceneBuilder::build() {
    while (reader.hasNext()) {
        std::string command(reader.readString());
        lowercase(command);
        commands[command]();
    }
    loadCurrentObj();
    return scene;
}

void SceneBuilder::defineCommands() {
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

void SceneBuilder::loadCurrentObj() {
    if (currentObj != nullptr) {
        currentObj->load();
        scene.addObj(currentObj);
    }
}

void SceneBuilder::lowercase(std::string& s) const {
    std::string result(s);
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
}
