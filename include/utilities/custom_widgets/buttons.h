#pragma once
#include "def.h"

namespace button_states{
    enum class COLLAPSE_EXPAND_STATE{
        COLLAPSED,
        EXPANDED
    };
}


class IconedButton:public QPushButton{
    Q_OBJECT
public:
    IconedButton(const QString& res_path,QWidget* parent):QPushButton(parent){
        setIcon(QIcon(res_path));
    }

    IconedButton(const QIcon& icon,QWidget* parent):QPushButton(parent){
        setIcon(icon);
    }

    IconedButton(QIcon&& icon,QWidget* parent):QPushButton(icon,"",parent){
        setIcon(icon);
    }

    IconedButton(QWidget* parent):QPushButton(parent){}

protected:
    void paintEvent(QPaintEvent *event) override {
            QPushButton::paintEvent(event); // Вызываем реализацию по умолчанию для отображения фона и текста
            QPainter painter(this);

            if (!icon().isNull()) {
                painter.setRenderHint(QPainter::SmoothPixmapTransform); // Сглаживание для иконки
                setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});

            }

        }
};

template<typename ENUM_STATE>
struct IconPathByState{
    ENUM_STATE state;
    QString path;
};

#include <QMap>
#include <QMap>
#include <QEvent>

template<typename ENUM_STATE>
class MultiStateIconedButton:public QPushButton{
public:
    MultiStateIconedButton(ENUM_STATE default_state,QList<IconPathByState<ENUM_STATE>> paths,QWidget* parent):
        QPushButton(parent),
        current_state_(default_state){
        for(const auto& icon:paths)
            icons_.insert(icon.state,QIcon(icon.path));
        setIcon(icons_.value(current_state_));
        assert(!icon().isNull());
    }

protected:

    bool event(QEvent* event) override{
        switch(event->type()){
        case QEvent::MouseButtonPress:
            return true;
            break;
        case QEvent::MouseButtonRelease:
            changeState();
            emit clicked(true);
            return true;
            break;
        case QEvent::Leave:
            return true;
            break;
        case QEvent::Paint:
            QPushButton::paintEvent(reinterpret_cast<QPaintEvent*>(event));
        default:
            break;
        }
        return false;
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);

        if (!icon().isNull()) {
            painter.setRenderHint(QPainter::SmoothPixmapTransform); // Сглаживание для иконки
            setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});

        }

    }

    virtual void changeState() = 0;
    ENUM_STATE current_state_;
    QMap<ENUM_STATE,QIcon> icons_;
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

class CloseButton:public IconedButton{
    Q_OBJECT
public:
    CloseButton(const QString& res_path,QWidget* parent):IconedButton(res_path,parent){
        setContentsMargins(0,0,0,0);
        setFixedSize(20,20);
    }
};

#include <QImage>
class ExpressionButton:public IconedButton{
    Q_OBJECT
public:
    ExpressionButton(const QString& res_path,QWidget* parent):IconedButton(res_path,parent){

        setContentsMargins(0,0,0,0);
        setFixedSize(45,45);
    }
};

class CollapseButton:public MultiStateIconedButton<button_states::COLLAPSE_EXPAND_STATE>{
    Q_OBJECT
public:
    CollapseButton(button_states::COLLAPSE_EXPAND_STATE default_val,const QString& collapsed_icon,const QString& expanded_icon,QWidget* parent):MultiStateIconedButton(
                    default_val,
                    {{button_states::COLLAPSE_EXPAND_STATE::COLLAPSED,collapsed_icon}, \
                    {button_states::COLLAPSE_EXPAND_STATE::EXPANDED,expanded_icon}}, \
                    parent)
    {
        setContentsMargins(0,0,0,0);
        setFixedSize(20,20);
    }

    virtual void changeState() override{
        using namespace button_states;
        switch(current_state_){
        case(COLLAPSE_EXPAND_STATE::COLLAPSED):
            current_state_ = COLLAPSE_EXPAND_STATE::EXPANDED;
            setIcon(icons_.value(COLLAPSE_EXPAND_STATE::EXPANDED));
            break;
        case(button_states::COLLAPSE_EXPAND_STATE::EXPANDED):
            current_state_ = COLLAPSE_EXPAND_STATE::COLLAPSED;
            setIcon(icons_.value(COLLAPSE_EXPAND_STATE::COLLAPSED));
            break;
        default:
            break;
        }
    }
};
