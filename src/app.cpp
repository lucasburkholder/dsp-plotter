#ifndef APP_CPP
#define APP_CPP

#include "imgui.h"

#include "app.h"

using namespace DSPPlotter;

void App::onFrame() {
    if (ImGui::Begin("Main window")) {
        ImGui::Text("Some text");
        ImGui::End();
    }
}

#endif /* APP_CPP */
