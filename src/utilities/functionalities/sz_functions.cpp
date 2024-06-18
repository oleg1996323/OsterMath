#include "utilities/functionalities/sz_functions.h"
#include "kernel/application.h"

namespace functional{

void fullscreen(QWidget* widget){
    QScreen *screen = kernel::Application::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    widget->resize(width,height);
}

void zero_margins(QWidget* widget){

}

}
