#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

// **When adding a field here, remember to also add it to both `saveConfig()` and `loadConfig()`**

struct TestBenchConfig {
    std::string inputFile = "hi";
};

class Controller {
public:   
    Controller();
    ~Controller();  

    void loadConfig(std::string file);
    void loadAudioFile(std::string path);

    // GETTERS
    std::string getAudioInputFile();
    const std::vector<std::vector<float>>& getInputAudioData();
    const std::vector<float>& getInputAudioTimes();
    TestBenchConfig& getConfig();

private:
    TestBenchConfig config;
    const std::string configFile = "testbench_config.json";
    
    std::vector<std::vector<float>> inputAudio; // Split format [[LLLLL], [RRRRR]]
    std::vector<float> inputAudio_times;

    void loadConfig();
    void saveConfig(); 
};


#endif /* CONTROLLER_H */
