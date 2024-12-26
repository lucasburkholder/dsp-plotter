#ifndef VIEW_CPP
#define VIEW_CPP

#include "view.h"
#include "imgui.h"

void View::init(Controller * _controller) {
    controller.reset(_controller);
}
void View::showMainWindow() {
    ImGui::Begin("LBDSP Test Bench");

    ImGui::Text("Hello world! %s", "This is the test bench");

    std::string configFile = "testbench_config.json";

    if (ImGui::Button("Save Config")) {
        controller->saveConfig(configFile);
    }
    ImGui::SameLine();
    if (ImGui::Button("Load Config")) {
        controller->loadConfig(configFile);
    }

    ImGui::End();
}
#endif /* VIEW_CPP */
