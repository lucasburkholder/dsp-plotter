#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

// **When adding a field here, remember to also add it to both `saveConfig()` and `loadConfig()`**

struct TestBenchConfig {
    std::string inputFile;
};

class Controller {
public:        
    void saveConfig(std::string fn); 
    void loadConfig(std::string fn);
};


#endif /* CONTROLLER_H */
