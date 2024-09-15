#include "utilities/sz_functions.h"
#include "kernel/application.h"

namespace functional{

QSize fullscreen_size(){
    QScreen *screen = kernel::Application::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    return {width,height};
}

}
