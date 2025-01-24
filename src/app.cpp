#ifndef APP_CPP
#define APP_CPP

#include <cstdio>
#include <cmath>    
#include "imgui.h"
#include "implot.h"
#include "app.h"
#include "tinywav.h"

using namespace DSPPlotter;

#define INPUT_FILE_PATH "audio/bass_jet.wav"
#define BUFFER_SIZE 512 // In samples per channel, used while loading file

void App::init() {
    // Load audio file
    TinyWav tw;
    tinywav_open_read(&tw, INPUT_FILE_PATH, TW_SPLIT);
    inputData.resize(tw.numFramesInHeader);
    float buf[tw.numChannels * BUFFER_SIZE];
    float * samplePtrs[tw.numChannels];
    for (int chan = 0; chan < tw.numChannels; chan++) {
        samplePtrs[chan] = buf + chan * BUFFER_SIZE;
    }
    
    uint32_t channelToRead = 0;
    uint32_t writeIdx = 0;
    while (1) {
        int numRead = tinywav_read_f(&tw, samplePtrs, BUFFER_SIZE);        
        memcpy(&inputData[writeIdx += numRead], samplePtrs[channelToRead], numRead * sizeof(float));
        if (numRead < BUFFER_SIZE) break;
    }

    // Do some processing (replace with DUT)
    // TODO replace with DUT
    outputData.resize(inputData.size());
    for (uint32_t i = 0; i < outputData.size(); i++) {
        outputData[i] = fabsf(inputData[i]) - 0.5; // ABS distortion
    }

    // Configure
    cfg.inOutOverlap = false;
    return;
}

void App::onFrame() {
    if (ImGui::Begin("Main window")) {
        // PLOTS
        if (cfg.inOutOverlap) {
            if (ImPlot::BeginPlot("Audio", ImVec2(-1, -1))) {
                ImPlot::PlotLine("Input audio", inputData.data(), inputData.size());
                ImPlot::PlotLine("Output audio", outputData.data(), outputData.size());
                ImPlot::EndPlot();
            }
        } else {
            if (ImPlot::BeginPlot("Input audio", ImVec2(-1, ImGui::GetContentRegionAvail().y / 2.f))) {
                ImPlot::PlotLine("Input audio", inputData.data(), inputData.size());
                ImPlot::EndPlot();
            }
            if (ImPlot::BeginPlot("Output audio", ImVec2(-1, ImGui::GetContentRegionAvail().y))) {
                ImPlot::PlotLine("Output audio", outputData.data(), outputData.size());
                ImPlot::EndPlot();
            }
        }
    }
    ImGui::End();
}

#endif /* APP_CPP */
