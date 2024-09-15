#pragma once

namespace oster::utilities::__interfaces__{
class BordersInterface{
public:
    BordersInterface();

    bool borders() const;
    void setBorders(bool);
    int border_radius() const;
    void setBorder_radius(int);
    bool rounded_borders() const;
    void setRounded_borders(bool);
    int line_width() const;
    void setLine_width(int);
private:
    int border_radius_;
    int line_width_;
    bool borders_;
    bool rounded_borders_;
};
}
