#ifndef APP_CPP
#define APP_CPP

#include <cstdio>
#include <cmath>
#include "imgui.h"
#include "implot.h"
#include "app.h"

using namespace DSPPlotter;

void App::init() {
    printf("Plotting App\n");
    inputData.resize(1000);
    outputData.resize(1000);
    for (uint32_t i = 0; i < inputData.size(); i++) {
        inputData[i] = sinf((float) i / 4.f);
        outputData[i] = 0.6f * sinf((float) i / 4.5f);
    }

    // Configure
    cfg.inOutOverlap = true;
    return;
}

void App::onFrame() {
    if (ImGui::Begin("Main window")) {
        // PLOTS
        if (cfg.inOutOverlap) {
            if (ImPlot::BeginPlot("Audio")) {
                ImPlot::PlotLine("Input audio", inputData.data(), inputData.size());
                ImPlot::PlotLine("Output audio", outputData.data(), outputData.size());
                ImPlot::EndPlot();
            }
        } else {
            if (ImPlot::BeginPlot("Input audio")) {
                ImPlot::PlotLine("Input audio", inputData.data(), inputData.size());
                ImPlot::EndPlot();
            }
            if (ImPlot::BeginPlot("Output audio")) {
                ImPlot::PlotLine("Output audio", outputData.data(), outputData.size());
                ImPlot::EndPlot();
            }
        }
    }
    ImGui::End();
}

#endif /* APP_CPP */
