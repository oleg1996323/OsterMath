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
#include "utilities/custom_widgets/buttons.h"

class VarListFrame:public QFrame, public Retranslatable{
    Q_OBJECT
public:
    VarListFrame(QWidget* parent);

    virtual void retranslate() override;

private:
    QVBoxLayout *gridLayout;
    QLabel *label_search_var_list;
    QLineEdit *search_var_list;
    QTableWidget *table_var_list;
};

class VarListTitleBar:public QFrame, public Retranslatable{
    Q_OBJECT
public:
    VarListTitleBar(QWidget* parent);

    virtual void retranslate() override;

private:
    QHBoxLayout* layout_;
    QSpacerItem *horizontalSpacer;
    QLabel *label_var_list;
    CloseCollapseButtons *collapse_var_list;
    CloseCollapseButtons *close_var_list;
};

class VarListDockWidget:public QDockWidget, public Retranslatable{
    Q_OBJECT
public:
    VarListDockWidget(QMainWindow* parent);

    virtual void retranslate() override;

private:
    VarListFrame* frame_;
    VarListTitleBar* titlebar_;
    QPalette* palette;

public slots:
    void collapse(){
        if(frame_->isHidden())
            frame_->show();
        else
            frame_->hide();
    }
};

