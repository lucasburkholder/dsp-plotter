#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP

#include <stdexcept>
#include <fstream>
#include "controller.h"
#include "json.hpp"

using json = nlohmann::json;

void Controller::saveConfig(std::string fn) {
    json j;
    j["testParam"] = 3.0;
    
    std::ofstream fout(fn);
    fout << j;
    fout.close();
}
void Controller::loadConfig(std::string fn) {
}

#endif /* CONTROLLER_CPP */
