#ifndef VIEW_CPP
#define VIEW_CPP

#include "view.h"
#include "imgui.h"

void View::showMainWindow() {
    ImGui::Begin("LBDSP Test Bench");

    ImGui::Text("Hello world! %s", "This is the test bench");

    ImGui::End();
}
#endif /* VIEW_CPP */
