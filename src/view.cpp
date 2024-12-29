#ifndef VIEW_CPP
#define VIEW_CPP

#include <iostream>

#include "view.h"
#include "imgui.h"
#include "implot.h"
#include "dialogs.h"

void View::showMainWindow() {
    ImGui::Begin("LBDSP Test Bench");

    ImGui::Text("Audio file: %s", controller->getAudioInputFile().c_str());
    ImGui::SameLine();
    if (ImGui::Button("Select file..."))
        askUserForAudioFile();

    ImGui::SeparatorText("File plot");
    if (ImPlot::BeginPlot("Input file")) {
        ImPlot::EndPlot();
    }
    ImGui::End();
}

/* PRIVATE */
void View::askUserForAudioFile() {
    std::string fp = openAudioFileDialog();
    if (fp != "") {
        auto& config = controller->getConfig();
        config.inputFile = fp;
        controller->loadAudioFile(fp);
    }
}

#endif /* VIEW_CPP */
