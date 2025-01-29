#ifndef APP_H
#define APP_H

#include <vector>
#include <cstdint>
#include "dsp-plotter.h"

namespace DSPPlotter {
    struct AppConfig {
        bool inOutOverlap = false;
    };
    class App {
    public:
        void init(char* wavFilePath, uint32_t frameSize, startupFunc_t, processFunc_t, shutdownFunc_t);
        void onFrame();

    private:
        AppConfig cfg;
        std::vector<float> inputData, outputData;
    };
}
#endif /* APP_H */
