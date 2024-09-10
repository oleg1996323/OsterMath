#pragma once
#include <QStyleOptionButton>
#include "styles/styles.h"

namespace style_options{
    class ButtonStyleOption:public QStyleOptionButton{
    public:
        enum {SO_AdvancedButton = QStyleOption::SO_CustomBase + 1};
        enum { Version = QStyleOptionButton::Version + 1 };
        ButtonStyleOption():QStyleOptionButton(Version)
        {
            type = SO_AdvancedButton;
            version = Version;
        }
        ButtonStyleOption(const ButtonStyleOption &other)
            : QStyleOptionButton(other),
              borders(other.borders),
              rounded_borders(other.rounded_borders),
              border_radius(other.border_radius)
        {
            type = SO_AdvancedButton; // Устанавливаем тип
            version = Version;
        }

        // Конструктор с базовым классом
        explicit ButtonStyleOption(const QStyleOptionButton &other)
            : QStyleOptionButton(other),
              borders(0),
              rounded_borders(0),
              border_radius(0)
        {
            this->type = Type;
        }

        bool borders = true;
        bool rounded_borders = false;
        int border_radius = Themes::border_round_common;
    };
}
