#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include "controller.h"

class View {
public:
    View(Controller * _controller) : controller(_controller) {}
    void showMainWindow();
private:
    Controller *controller;

    void askUserForAudioFile();
};

#endif /* VIEW_H */
