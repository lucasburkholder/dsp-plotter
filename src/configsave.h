#ifndef CONFIGSAVE_H
#define CONFIGSAVE_H

#include <string>

// **When adding a field here, remember to also add it to both `saveConfig()` and `loadConfig()`**

struct ATWConfig {
    std::string inputFile;
};

void saveConfig(std::string fn); 
void loadConfig(std::string fn);

#endif /* CONFIGSAVE_H */
