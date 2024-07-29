#pragma once
#include <QToolBar>
#include <QTabWidget>
#include "toolbartabs.h"

namespace ToolBar{

    class BookToolBar:public QToolBar{
        Q_OBJECT
    public:
        BookToolBar(QWidget* parent):QToolBar(parent){
            setFloatable(false);
            setMovable(false);
            setContentsMargins(10,5,10,5);
            setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            QFont font;

            font.setFamily("FreeSans");
            font.setPointSize(8);
            font.setBold(true);
            setFont(font);

            tabs_=new BookTools(this);
            addWidget(tabs_);
        }
    private:
        BookTools *tabs_;
    };
}
