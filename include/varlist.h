#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QDockWidget>
#include <QToolBar>
#include <QShowEvent>
#include <QDebug>
#include "utilities/custom_widgets/buttons.h"

namespace VarList {

class Frame:public QFrame, public Retranslatable{
    Q_OBJECT

    class Label:public QLabel{
    public:
        Label(QWidget* parent);
    };
    class SearchLine:public QLineEdit{
    public:
        SearchLine(QWidget* parent);
    };
    class Table:public QTableWidget{
    public:
        Table(QWidget* parent);

    };

public:
    Frame(QWidget* parent);

    virtual void retranslate() override;

private:

    QVBoxLayout *gridLayout;
    Label *label_search_var_list;
    SearchLine *search_var_list;
    Table *table_var_list;

    virtual void showEvent(QShowEvent* event) override{
        updateGeometry();
    }

};

class TitleBar:public QFrame, public Retranslatable{
    Q_OBJECT
public:
    TitleBar(QWidget* parent);

    virtual void retranslate() override;

private:
    class Label:public QLabel{
    public:
        Label(QWidget* parent):QLabel(parent){
            setContentsMargins(0,0,0,0);
            setObjectName(QString::fromUtf8("varlisttitlebar_label"));
            QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            setSizePolicy(sizePolicy);
            setMaximumSize(QSize(2000, 20));
            QFont font;
            font.setFamily("Sans");
            font.setPointSize(10);
            font.setBold(true);
            font.setWeight(100);
            setFont(font);
        }
    };

    QHBoxLayout* layout_;
    QSpacerItem *horizontalSpacer;
    Label *label_var_list;
    CollapseButton *collapse_var_list;
    CloseButton *close_var_list;
};

class DockWidget:public QDockWidget, public Retranslatable{
    Q_OBJECT
public:
    DockWidget(QMainWindow* parent);

    virtual void retranslate() override;

private:
    Frame* frame_;
    TitleBar* titlebar_;
    QPalette* palette;
    QSize last_size;

public slots:
    void collapse(){
        if(frame_->isHidden()){
            frame_->show();
            resize(last_size);
        }
        else{
            last_size = size();
            frame_->hide();
        }
    }
};

}
