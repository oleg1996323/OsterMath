#pragma once
#include "kernel/def.h"
#include <QMouseEvent>

namespace button_states{
    enum class COLLAPSE_EXPAND_STATE{
        COLLAPSED,
        EXPANDED
    };
}

Q_DECLARE_METATYPE(button_states::COLLAPSE_EXPAND_STATE)

class IconedButton:public QPushButton{
    Q_OBJECT
public:
    IconedButton(const QString& res_path,QWidget* parent);
    IconedButton(const QIcon& icon,QWidget* parent);
    IconedButton(QIcon&& icon,QWidget* parent);
    IconedButton(QWidget* parent);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    bool icon_set_ = false;
};

template<typename ENUM_STATE>
struct IconPathByState{
    ENUM_STATE state;
    QIcon path;
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
        setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
        connect(this,&QPushButton::clicked,[&](){changeState();});
    }
protected:

    virtual void paintEvent(QPaintEvent *event) override{
        QPushButton::paintEvent(event);
    }
    virtual void changeState() = 0;
    ENUM_STATE current_state_;
    QMap<ENUM_STATE,QIcon> icons_;
};

class ToolButton:public QPushButton{
    Q_OBJECT
public:
    ToolButton(const QString& res_path,QWidget* parent);
};

class CloseButton:public QPushButton{
    Q_OBJECT
public:
    CloseButton(const QString& res_path,QWidget* parent);
    virtual void paintEvent(QPaintEvent*) override;
};

class CollapseButton:public MultiStateIconedButton<button_states::COLLAPSE_EXPAND_STATE>{
    Q_OBJECT
public:
    CollapseButton(button_states::COLLAPSE_EXPAND_STATE default_val,const QString& collapsed_icon,const QString& expanded_icon,QWidget* parent);
    virtual void changeState() override;
    virtual void paintEvent(QPaintEvent*) override;
};
