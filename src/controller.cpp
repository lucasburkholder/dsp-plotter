#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include "controller.h"
#include "json.hpp"

using json = nlohmann::json;

Controller::Controller() {
    loadConfig();
}

Controller::~Controller() {
    saveConfig();
}

void Controller::loadAudioFile(std::string path) {
    std::cout << "loadAudioFile not implemented yet" << std::endl;
}

/* ---- GETTERS ------ */
std::string Controller::getAudioInputFile() {
    return config.inputFile;
}

TestBenchConfig& Controller::getConfig() {
    return config;
}

/* ----- PRIVATE ----- */
void Controller::saveConfig() {
    json j;
    j["inputFile"] = config.inputFile;
    
    std::string jsonOut = j.dump();

    std::ofstream fout(configFile);
    if (fout.fail()) {
        printf("Could not save config file\n");
        return;
    }
    fout << j.dump();
    fout.close();
    printf("Saved config file: %s\n", configFile.c_str());
}
void Controller::loadConfig() {
    std::ifstream fin(configFile);
    if (fin.fail()) {
        printf("Could not load config file\n");
        return;
    }
    json j = json::parse(fin);
    fin.close();

    config.inputFile = std::string(j["inputFile"]);
    
    printf("Loaded config file: %s\n", configFile.c_str());
    printf("\tinputFile: %48s\n", config.inputFile.c_str());
}

#endif /* CONTROLLER_CPP */
