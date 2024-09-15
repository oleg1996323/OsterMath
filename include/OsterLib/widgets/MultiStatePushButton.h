#pragma once
#include "PushButton.h"
#include <QIcon>
#include <QMap>

template<typename ENUM_STATE>
struct IconPathByState{
    ENUM_STATE state;
    QIcon path;
};

template<typename ENUM_STATE>
class MultiStateIconedButton:public IconedButton{
public:
    MultiStateIconedButton(ENUM_STATE default_state,QList<IconPathByState<ENUM_STATE>> paths,QWidget* parent):
        IconedButton(parent),
        current_state_(default_state){
        for(const auto& icon:paths)
            icons_.insert(icon.state,QIcon(icon.path));
        setIcon(icons_.value(current_state_));
        assert(!icon().isNull());
        setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
        connect(this,&PushButton::clicked,[&](){changeState();});
    }
protected:
    virtual void changeState() = 0;
    ENUM_STATE current_state_;
    QMap<ENUM_STATE,QIcon> icons_;
};

enum class CollapseButtonState{
    COLLAPSED,
    EXPANDED
};

class CollapseButton:public MultiStateIconedButton<CollapseButtonState>{
    Q_OBJECT
public:

    CollapseButton(CollapseButtonState default_val,const QString& collapsed_icon,const QString& expanded_icon,QWidget* parent);
    virtual void changeState() override;
    virtual void paintEvent(QPaintEvent*) override;
};

Q_DECLARE_METATYPE(CollapseButtonState)
