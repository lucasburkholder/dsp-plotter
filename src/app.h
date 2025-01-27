#ifndef APP_H
#define APP_H

#include <vector>
#include <cstdint>

namespace DSPPlotter {
    struct AppConfig {
        bool inOutOverlap = false;
    };
    class App {
    public:
        void init(char* wavFilePath);
        void onFrame();

    private:
        AppConfig cfg;
        std::vector<float> inputData, outputData;
    };
}
#endif /* APP_H */
