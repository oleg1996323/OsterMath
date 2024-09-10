#pragma once
#include <QStyleOptionButton>
#include <QPainterPath>
#include "styles/styles.h"

namespace style_options{
    class ButtonStyleOption:public QStyleOptionButton{
    public:
        enum {Type = Themes::SO_AdvancedPushButton};
        ButtonStyleOption():QStyleOptionButton()
        {
            type = Type;
        }
        ButtonStyleOption(const ButtonStyleOption &other)
            : QStyleOptionButton(other),
              borders(other.borders),
              rounded_borders(other.rounded_borders),
              border_radius(other.border_radius),
              path(other.path)
        {
            type = Type; // Устанавливаем тип
        }
        // Конструктор с базовым классом
        explicit ButtonStyleOption(const QStyleOptionButton &other)
            : QStyleOptionButton(other),
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
