#ifndef APP_CPP
#define APP_CPP

#include <cstdio>
#include <cmath>
#include <algorithm> 
#include "imgui.h"
#include "implot.h"
#include "app.h"
#include "tinywav.h"

using namespace DSPPlotter;

#define BUFFER_SIZE 512 // In samples per channel, used while loading file

void App::init(char* wavFilePath, uint32_t frameSize, startupFunc_t startupFunc, processFunc_t processFunc, shutdownFunc_t shutdownFunc) {
    // Load audio file
    TinyWav tw;
    tinywav_open_read(&tw, wavFilePath, TW_SPLIT);
    inputData.resize(tw.numFramesInHeader);
    float buf[tw.numChannels * BUFFER_SIZE];
    float * samplePtrs[tw.numChannels];
    for (int chan = 0; chan < tw.numChannels; chan++) {
        samplePtrs[chan] = buf + chan * BUFFER_SIZE;
    }

    if (tw.numChannels > 0) {
        printf("Selected file has %d channels, but plotter only currently supports 1. Ignoring all channels except the first.\n", tw.numChannels);
    }    

    uint32_t channelToRead = 0;
    uint32_t writeIdx = 0;
    while (1) {
        int numRead = tinywav_read_f(&tw, samplePtrs, BUFFER_SIZE);        
        memcpy(&inputData[writeIdx += numRead], samplePtrs[channelToRead], numRead * sizeof(float));
        if (numRead < BUFFER_SIZE) break;
    }

    // Do some processing (replace with DUT)
    int err;
    outputData.resize(inputData.size());

    err = (*startupFunc)();
    if (err) fprintf(stderr, "Error in startup function: %d\n", err);

    uint32_t idx = 0;
    while (1) {
        if (idx + frameSize > inputData.size()) {
            // Not enough samples left: zero-pad, process and break
            std::vector<float> lastFrame_in(frameSize, 0.f);
            std::vector<float> lastFrame_out(frameSize, 0.f);
           
            std::copy(inputData.begin() + idx, inputData.end(), lastFrame_in.begin());

            err = (*processFunc)(lastFrame_in.data(), lastFrame_out.data());
            if (err) fprintf(stderr, "Error in process function: %d\n", err);

            // std::copy(lastFrame_out.begin(), lastFrame_out.begin(), outputData.begin() + idx);
            std::copy_n(lastFrame_out.data(), outputData.size() - idx, outputData.begin() + idx);
            
            break;
        }
        err = (*processFunc)(&inputData[idx], &outputData[idx]);
        if (err) fprintf(stderr, "Error in process function: %d\n", err);

        idx += frameSize;
    }
    

    err = (*shutdownFunc)();
    if (err) fprintf(stderr, "Error in shutdown function: %d\n", err);

    // Close file
    tinywav_close_read(&tw);

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
