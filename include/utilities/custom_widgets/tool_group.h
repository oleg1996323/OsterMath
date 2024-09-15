#pragma once
#include <QGroupBox>
#include <QGridLayout>
#include "PushButton.h"
#include "styles.h"

class Group:public QGroupBox{
public:
    Group(const QString& title,QWidget* parent);
    QGridLayout* grid_layout();
    virtual QSize sizeHint() const override;
protected:
    class ToolButton:public IconedButton{
    public:
        ToolButton(const QString& icon_res,QWidget* parent):IconedButton(icon_res,parent){
            set_size({30,30});
            setBorders(true);
            setRounded_borders(true);
            setLine_width(1);
            setBorder_radius(Themes::border_round_common);
        }
    };
private:
    QGridLayout* layout_;
};
