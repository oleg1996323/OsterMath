#pragma once
#include <QStyleOptionFrame>
#include <QPainterPath>
#include "styles/styles.h"

namespace style_options{
    class LineEditStyleOption:public QStyleOptionFrame{
    public:
        enum {Type = Themes::SO_AdvancedLineEdit};
        LineEditStyleOption():QStyleOptionFrame()
        {
            type = Type;
        }
        LineEditStyleOption(const LineEditStyleOption &other)
            : QStyleOptionFrame(other),
              borders(other.borders),
              rounded_borders(other.rounded_borders),
              border_radius(other.border_radius),
              path(other.path)
        {
            type = Type; // Устанавливаем тип
        }
        // Конструктор с базовым классом
        explicit LineEditStyleOption(const QStyleOptionFrame &other)
            : QStyleOptionFrame(other),
              borders(0),
              rounded_borders(0),
              border_radius(0),
              path(QPainterPath())
        {
            this->type = QStyleOptionButton::Type;
        }

        void set_rounded(bool a){
            if(a){
                path.addRoundedRect(rect,border_radius,border_radius);
            }
            else{
                path = QPainterPath();
            }
        }

        bool rounded() const{
            return rounded_borders;
        }

        bool borders = true;
        int border_radius = Themes::border_round_common;
        mutable QPainterPath path;
    private:
        bool rounded_borders = false;
    };
}
