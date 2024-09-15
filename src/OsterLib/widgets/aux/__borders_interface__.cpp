#include "aux/__borders_interface__.h"
#include "styles.h"

namespace oster::utilities::__interfaces__{
BordersInterface::BordersInterface():
    border_radius_(Themes::border_round_common){}

bool BordersInterface::borders() const{
    return borders_;
}
void BordersInterface::setBorders(bool a){
    borders_ = a;
}
int BordersInterface::border_radius() const{
    return border_radius_;
}
void BordersInterface::setBorder_radius(int a){
    border_radius_ = a;
}
bool BordersInterface::rounded_borders() const{
    return rounded_borders_;
}
void BordersInterface::setRounded_borders(bool a){
    rounded_borders_ = a;
}

int BordersInterface::line_width() const{
    return line_width_;
}
void BordersInterface::setLine_width(int w){
    line_width_ = w;
}
}
