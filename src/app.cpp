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
    return;
}

void App::onFrame() {
    std::vector<float> inputData(100000);
    std::vector<float> outputData(10000);
    for (uint32_t i = 0; i < inputData.size(); i++) {
        inputData[i] = sinf((float) i / 4.f);
    }
    if (ImGui::Begin("Main window")) {
        if (ImPlot::BeginPlot("Input audio")) {
            ImPlot::PlotLine("Input audio", inputData.data(), inputData.size());
            ImPlot::EndPlot();
        }
    }
    ImGui::End();
}

#endif /* APP_CPP */
