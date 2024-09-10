#pragma once
#include <QStyleOption>
#include "styles/styles.h"

namespace style_options{
    class LineEditStyleOption:public QStyleOption{
    public:
        bool borders = true;
        bool rounded_borders = false;
        int border_radius = Themes::border_round_common;
    };
}
