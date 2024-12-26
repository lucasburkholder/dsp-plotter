#ifndef VIEW_CPP
#define VIEW_CPP

#include <iostream>

#include "view.h"
#include "imgui.h"

void View::init(Controller * _controller) {
    controller.reset(_controller);
}
void View::showMainWindow() {
    ImGui::Begin("LBDSP Test Bench");

    ImGui::Text("Audio file: %s", controller->getAudioInputFile().c_str());
    ImGui::SameLine();
    if (ImGui::Button("Select file..."))
        askUserForAudioFile();

    ImGui::End();
}

/* PRIVATE */
void View::askUserForAudioFile() {
    char buf[256];
    printf("Enter file: ");
    scanf("%s", buf);
    auto& config = controller->getConfig();
    config.inputFile = std::string(buf);
}

#endif /* VIEW_CPP */
