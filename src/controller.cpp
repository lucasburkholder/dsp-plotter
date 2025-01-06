#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include "controller.h"
#include "json.hpp"

#include "tinywav.h"

using json = nlohmann::json;

Controller::Controller() {
    loadConfig();
    loadAudioFile(config.inputFile);
}

Controller::~Controller() {
    saveConfig();
}

void Controller::loadAudioFile(std::string path) {
    int err;
    TinyWav tw;
    TinyWavChannelFormat fmt = TinyWavChannelFormat::TW_SPLIT;
    err = tinywav_open_read(&tw, path.c_str(), fmt);
    if (err) {
        char msg[32];
        sprintf(&msg[0], "Tinywav error opening file: %d\n", err);
        throw std::runtime_error(msg);
    }
    
    if (tw.sampFmt != TinyWavSampleFormat::TW_FLOAT32) {
        std::cout << "Wav is int, not float. Ignoring";
        return;
    }
    std::cout << "Num channels: " << tw.numChannels << std::endl;
    std::cout << "Num frames (according to header): " << tw.numFramesInHeader << std::endl;
        
    // Allocate space
    inputAudio.resize(
        tw.numChannels,
        std::vector<float>(tw.numFramesInHeader, 0.f)
    );
    inputAudio_times.resize(tw.numFramesInHeader);
    
    float * bufPtr[tw.numChannels];
    for (uint32_t i = 0; i < tw.numChannels; i++)
        bufPtr[i] = inputAudio[i].data();

    // FIXME: error here because not enough stack space available.
    // Split into smaller blocks
    // --- begin copilot code
    uint32_t blockSize = 1024; // Define a block size
    uint32_t framesRemaining = tw.numFramesInHeader;
    uint32_t offset = 0;

    while (framesRemaining > 0) {
        uint32_t framesToRead = std::min(blockSize, framesRemaining);
        int numRead = tinywav_read_f(&tw, bufPtr, framesToRead);
        if (numRead != framesToRead) {
            throw std::runtime_error("Error reading audio file in blocks");
        }
        framesRemaining -= numRead;
        offset += numRead;
        for (uint32_t i = 0; i < tw.numChannels; i++) {
            bufPtr[i] += numRead;
        }
    }
    // --- end copilot code

    for (uint32_t i=0; i < tw.numFramesInHeader; i++)
        inputAudio_times[i] = i;

    // int numRead = tinywav_read_f(&tw, bufPtr, tw.numFramesInHeader);
    // assert(numRead == tw.numFramesInHeader);
    printf("Audio file loaded\n");
}

/* ---- GETTERS ------ */
std::string Controller::getAudioInputFile() {
    return config.inputFile;
}

const std::vector<std::vector<float>>& Controller::getInputAudioData() {
    return inputAudio;
}

const std::vector<float>& Controller::getInputAudioTimes() {
    return inputAudio_times;
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
