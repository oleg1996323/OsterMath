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
#include <QMainWindow>
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
    class Table:public QTableWidget, public Retranslatable{
    public:
        Table(QWidget* parent);

        virtual void retranslate() override{
            QTableWidgetItem *___qtablewidgetitem = horizontalHeaderItem(0);
            ___qtablewidgetitem->setText(QCoreApplication::translate("BookMath", "\320\230\320\274\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
            QTableWidgetItem *___qtablewidgetitem1 = horizontalHeaderItem(1);
            ___qtablewidgetitem1->setText(QCoreApplication::translate("BookMath", "\320\242\320\270\320\277", nullptr));
            QTableWidgetItem *___qtablewidgetitem2 = horizontalHeaderItem(2);
            ___qtablewidgetitem2->setText(QCoreApplication::translate("BookMath", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
            insertColumn(1);
        }
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

    void setVertical(){
        common_layout_=new QVBoxLayout(this);
        QVBoxLayout* layout_ = qobject_cast<QVBoxLayout*>(common_layout_);
        layout_->setSpacing(0);
        layout_->setContentsMargins(0,0,0,0);
        layout_->setObjectName(QString::fromUtf8("varlisttitlebar_layout"));
        layout_->setSizeConstraint(QLayout::SetNoConstraint);

        layout_->addWidget(label_var_list,Qt::AlignLeft);
        layout_->addItem(horizontalSpacer);
        layout_->addWidget(collapse_var_list,Qt::AlignRight);
        layout_->addWidget(close_var_list,Qt::AlignRight);

        setLayout(layout_);
    }

    void setHorizontal(){
        common_layout_=new QHBoxLayout(this);
        QHBoxLayout* layout_ = qobject_cast<QHBoxLayout*>(common_layout_);
        layout_->setSpacing(0);
        layout_->setContentsMargins(0,0,0,0);
        layout_->setObjectName(QString::fromUtf8("varlisttitlebar_layout"));
        layout_->setSizeConstraint(QLayout::SetNoConstraint);

        layout_->addWidget(label_var_list,Qt::AlignLeft);
        layout_->addItem(horizontalSpacer);
        layout_->addWidget(collapse_var_list,Qt::AlignRight);
        layout_->addWidget(close_var_list,Qt::AlignRight);

        setLayout(layout_);
    }

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

    QLayout* common_layout_;
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
            setFeatures(DockWidgetFloatable | DockWidgetClosable | DockWidgetMovable |DockWidgetMovable);
            titlebar_->setHorizontal();
            repaint();
        }
        else{
            last_size = size();
            frame_->hide();
            setFeatures(QDockWidget::DockWidgetVerticalTitleBar);
            titlebar_->setVertical();
            repaint();
        }
    }

    virtual void closeEvent(QCloseEvent *event) override{
        (void)event;
        if(qobject_cast<QMainWindow*>(parentWidget())->dockWidgetArea(this)!=Qt::NoDockWidgetArea)
            qobject_cast<QMainWindow*>(parentWidget())->removeDockWidget(this);
    }

    virtual void showEvent(QShowEvent *event) override{
        (void)event;
        qobject_cast<QMainWindow*>(parentWidget())->addDockWidget(Qt::LeftDockWidgetArea,this);
    }
};

}
