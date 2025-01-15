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
        void init();
        void onFrame();

    private:
        AppConfig cfg;
    };
}
#endif /* APP_H */
