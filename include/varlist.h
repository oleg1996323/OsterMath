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
#include "utilities/custom_widgets/buttons.h"

namespace VarList {

class Frame:public QFrame, public Retranslatable{
    Q_OBJECT

    class Label:public QLabel{
    public:
        Label(QWidget* parent);

    private:
        void showEvent(QShowEvent *event) override{
            (void)event;
            updateGeometry();
        }
    };

    class SearchLine:public QLineEdit{
    public:
        SearchLine(QWidget* parent);
    private:
        void showEvent(QShowEvent *event) override;
    };

    class Table:public QTableWidget{
    public:
        Table(QWidget* parent);
    private:
        QSize last_size;
        void showEvent(QShowEvent *event) override{
            setGeometry(pos().x(),pos().y(),last_size.width(),last_size.height());
        }
    };

public:
    Frame(QWidget* parent);

    virtual void retranslate() override;

    void showEvent(QShowEvent *event) override{
        (void)event;
        updateGeometry();
    }

private:

    QVBoxLayout *gridLayout;
    Label *label_search_var_list;
    SearchLine *search_var_list;
    Table *table_var_list;

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

        }

    private:
        void showEvent(QShowEvent *event) override{
            (void)event;
            updateGeometry();
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

public slots:
    void collapse(){
        if(frame_->isHidden())
            frame_->show();
        else
            frame_->hide();
    }
};

}
