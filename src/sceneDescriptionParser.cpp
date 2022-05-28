#include "cylinder.hpp"
#include "fileTokenReader.hpp"
#include "plane.hpp"
#include "sceneDescriptionParser.hpp"
#include "sphere.hpp"

#include <functional>
#include <string>

SceneDescrParser::SceneDescrParser(const fs::path& descr) : descr(descr), reader(descr), currentObj(nullptr) {
    defineCommands();
}

Scene SceneDescrParser::parse() {
	bvh = std::make_shared<Bvh>();
    while (reader.hasNext()) {
        std::string command(reader.readString());
        if (command == commentDelimiter) {
			skipComment();
        } else {
			lowercase(command);
			commands[command]();
		}
    }
    loadCurrentObj();
	bvh->loadFinal();
	if (!bvh->isEmpty()) scene.addObj(bvh);
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
        Vec3 camDir = reader.readVec3().normalized();
        scene.setCam(camPos, camDir);
    };
    commands["sphere"] = [&] {
        loadCurrentObj();
        currentObj = std::make_shared<Sphere>();
    };
	commands["plane"] = [&] {
		loadCurrentObj();
		currentObj = std::make_shared<Plane>();
	};
	commands["cylinder"] = [&] {
		loadCurrentObj();
		currentObj = std::make_shared<Cylinder>();
	};
    commands["smf"] = [&] {
        loadCurrentObj();
        currentObj = bvh;
		bvh->setNextSmf(reader.readString());
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
        currentObj->color(reader.readVec3());
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
        Rgb color = reader.readVec3();
        scene.addPointLight(PointLight(pos, color));
    };
}

void SceneDescrParser::skipComment() {
    while (reader.readString() != commentDelimiter)
        ;
}

void SceneDescrParser::loadCurrentObj() {
    if (currentObj != nullptr) {
        currentObj->load();
        scene.addObj(currentObj);
    }
}

void SceneDescrParser::lowercase(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
}
