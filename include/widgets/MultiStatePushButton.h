#pragma once
#include "PushButton.h"
#include <QIcon>
#include <QMap>

template<typename ENUM_STATE>
struct IconPathByState{
    ENUM_STATE state;
    QIcon path;
};

enum class COLLAPSE_EXPAND_STATE{
    COLLAPSED,
    EXPANDED
};

template<typename ENUM_STATE>
class MultiStateIconedButton:public PushButton{
public:
    MultiStateIconedButton(ENUM_STATE default_state,QList<IconPathByState<ENUM_STATE>> paths,QWidget* parent):
        PushButton(parent),
        current_state_(default_state){
        for(const auto& icon:paths)
            icons_.insert(icon.state,QIcon(icon.path));
        setIcon(icons_.value(current_state_));
        assert(!icon().isNull());
        setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
        connect(this,&PushButton::clicked,[&](){changeState();});
    }
protected:

    virtual void paintEvent(QPaintEvent *event) override{
        PushButton::paintEvent(event);
    }
    virtual void changeState() = 0;
    ENUM_STATE current_state_;
    QMap<ENUM_STATE,QIcon> icons_;
};

Q_DECLARE_METATYPE(COLLAPSE_EXPAND_STATE)

class CollapseButton:public MultiStateIconedButton<COLLAPSE_EXPAND_STATE>{
    Q_OBJECT
public:
    CollapseButton(COLLAPSE_EXPAND_STATE default_val,const QString& collapsed_icon,const QString& expanded_icon,QWidget* parent);
    virtual void changeState() override;
    virtual void paintEvent(QPaintEvent*) override;
};
