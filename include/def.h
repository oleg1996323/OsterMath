#pragma once
#include <QPushButton>
#include <QCommonStyle>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QStringList>
#include <QArrayData>

constexpr std::array<const char*,3> format_={".xlsx",".omb",".ods"};

class Retranslatable{
    virtual void retranslate() = 0;
};

class IconedButton:public QPushButton{
    Q_OBJECT
public:
    IconedButton(const QString& res_path,QWidget* parent):QPushButton(QIcon(res_path),"",parent){
    }

protected:
    void paintEvent(QPaintEvent *event) override {
            QPushButton::paintEvent(event); // Вызываем реализацию по умолчанию для отображения фона и текста

            if (!icon().isNull()) {
                QPainter painter(this);
                painter.setRenderHint(QPainter::SmoothPixmapTransform); // Сглаживание для иконки

                // Рисуем иконку на всю область кнопки
                QRect iconRect = QRect(0, 0, width(), height());
                painter.drawPixmap(iconRect, icon().pixmap(iconRect.size()));
            }
        }
};

class ToolButton:public IconedButton{
    Q_OBJECT
public:
    ToolButton(const QString& res_path,QWidget* parent):IconedButton(res_path,parent){
//        setStyleSheet("image: url("+res_path+");"
//                    "background-color: "+ parent->palette().color(QPalette::Button).name(QColor::HexRgb)+";");

        setContentsMargins(0,0,0,0);
        setFixedSize(35,35);
    }
};

class CloseCollapseButtons:public IconedButton{
    Q_OBJECT
public:
    CloseCollapseButtons(const QString& res_path,QWidget* parent):IconedButton(res_path,parent){
        setContentsMargins(0,0,0,0);
        setFixedSize(20,20);
    }
};
