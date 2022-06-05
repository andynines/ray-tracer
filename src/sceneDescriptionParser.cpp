#include "bumpSphere.hpp"
#include "cylinder.hpp"
#include "fileTokenReader.hpp"
#include "plane.hpp"
#include "sceneDescriptionParser.hpp"
#include "sphere.hpp"
#include "textureSphere.hpp"

#include <functional>
#include <string>

SceneDescrParser::SceneDescrParser(const fs::path& descr) : descr(descr), reader(descr), currentObj(nullptr) {
    defineCommands();
}

Scene SceneDescrParser::parse() {
	bvh = std::make_shared<Bvh>();
    while (reader.hasNext()) {
        std::string command = reader.readString();
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
	commands["texsphere"] = [&] {
		loadCurrentObj();
		currentObj = std::make_shared<TexSphere>(reader.readString());
	};
	commands["bumpsphere"] = [&] {
		loadCurrentObj();
		currentObj = std::make_shared<BumpSphere>(reader.readString());
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
        double ang = toRad(reader.readFloat());
        Vec3 ax = reader.readVec3();
        currentObj->rotate(ang, ax);
    };
    commands["scale"] = [&] {
        currentObj->scale(reader.readFloat());
    };
    commands["ambient"] = [&] {
		currentObj->setAmbient(reader.readFloat());
	};
	commands["diffuse"] = [&] {
		double kd = reader.readFloat();
		Rgb diffuse = reader.readVec3();
		currentObj->setDiffuse(kd, diffuse);
	};
	commands["specular"] = [&] {
		double ks = reader.readFloat();
		Rgb specular = reader.readVec3();
		currentObj->setSpecular(ks, specular);
	};
    commands["shiny"] = [&] {
        currentObj->setShiny(reader.readFloat());
    };
	commands["reflective"] = [&] {
		currentObj->setReflective(reader.readFloat());
	};
	commands["transmissive"] = [&] {
		double kt = reader.readFloat();
		Rgb transmissive = reader.readVec3();
		currentObj->setTransmissive(kt, transmissive);
	};
    commands["pointlight"] = [&] {
        Vec3 pos = reader.readVec3();
        Rgb color = reader.readVec3();
        scene.addPointLight(pos, color);
    };
	commands["spotlight"] = [&] {
		Vec3 pos = reader.readVec3();
		Rgb color = reader.readVec3();
		Vec3 dir = reader.readVec3().normalized();
		double cutoff = toRad(reader.readFloat());
		double sharpness = reader.readFloat();
		scene.addSpotLight(pos, color, dir, cutoff, sharpness);
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
