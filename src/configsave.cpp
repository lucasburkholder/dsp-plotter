#ifndef CONFIGSAVE_CPP
#define CONFIGSAVE_CPP

#include <stdexcept>
#include <fstream>
#include "configsave.h"

void saveConfig(std::string fn) {
    std::ofstream fout (fn);
    
    
}
void loadConfig(std::string fn) {
    throw std::logic_error("Not implemented");
}

#endif /* CONFIGSAVE_CPP */
