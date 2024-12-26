#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include "controller.h"

class View {
public:
    void init(Controller * _controller);
    void showMainWindow();
private:
    std::unique_ptr<Controller> controller;
};

#endif /* VIEW_H */
