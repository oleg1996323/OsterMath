#pragma once
#include "kernel/settings.h"
#include <QVariant>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QDockWidget>
#include <QToolBar>
#include <QShowEvent>
#include <QDebug>
#include <QMainWindow>
#include "utilities/custom_widgets/buttons.h"
#include "model/varlistmodel.h"

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
    class Table:public QTableView, public Retranslatable{
        model::Variables* var_list_;
    public:
        Table(QWidget* parent);

        virtual void retranslate() override{
//            QTableWidgetItem *___qtablewidgetitem = horizontalHeaderItem(0);
//            ___qtablewidgetitem->setText(QCoreApplication::translate("BookMath", "\320\230\320\274\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271", nullptr));
//            QTableWidgetItem *___qtablewidgetitem1 = horizontalHeaderItem(1);
//            ___qtablewidgetitem1->setText(QCoreApplication::translate("BookMath", "\320\242\320\270\320\277", nullptr));
//            QTableWidgetItem *___qtablewidgetitem2 = horizontalHeaderItem(2);
//            ___qtablewidgetitem2->setText(QCoreApplication::translate("BookMath", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
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

//    void setVertical(){
//        common_layout_->deleteLater();
//        common_layout_=new QVBoxLayout(this);
//        QVBoxLayout* layout_ = reinterpret_cast<QVBoxLayout*>(common_layout_);
//        layout_->setSpacing(0);
//        layout_->setContentsMargins(0,0,0,0);
//        layout_->setObjectName(QString::fromUtf8("varlisttitlebar_layout"));
//        layout_->setSizeConstraint(QLayout::SetMinimumSize);

//        layout_->addWidget(close_var_list,Qt::AlignTop);
//        layout_->addWidget(collapse_var_list,Qt::AlignTop);
//        QSpacerItem *spacer = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Expanding);
//        layout_->addSpacerItem(spacer);
//        layout_->addWidget(label_var_list,Qt::AlignBottom);
//        //label_var_list->vertical();

//        setLayout(common_layout_);
//    }

    void setHorizontal(){
        common_layout_=new QHBoxLayout(this);

        QHBoxLayout* layout_ = qobject_cast<QHBoxLayout*>(common_layout_);
        layout_->setSpacing(0);
        layout_->setContentsMargins(0,0,0,0);
        layout_->setObjectName(QString::fromUtf8("varlisttitlebar_layout"));
        layout_->setSizeConstraint(QLayout::SetMinimumSize);

        layout_->addWidget(label_var_list,Qt::AlignLeft);
        QSpacerItem *spacer = new QSpacerItem(20, 20,QSizePolicy::Expanding, QSizePolicy::Maximum);
        layout_->addSpacerItem(spacer);
        layout_->addWidget(collapse_var_list,Qt::AlignRight);
        layout_->addWidget(close_var_list,Qt::AlignRight);

        setLayout(common_layout_);

    }

private:
    class Label:public QLabel{
    public:
        Label(QWidget* parent):QLabel(parent){
            setContentsMargins(0,0,0,0);
            setObjectName(QString::fromUtf8("varlisttitlebar_label"));
            QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
            setSizePolicy(sizePolicy);
            setMaximumSize(QSize(2000, 20));
            QFont font;
            font.setFamily("Sans");
            font.setPointSize(10);
            font.setBold(true);
            font.setWeight(100);
            setFont(font);
            __load_settings__();
        }

        ~Label(){
            __save_settings__();
        }

        void __load_settings__(){
            QSettings* sets_ = kernel::settings::Program::get_settings();
            sets_->beginGroup("varlist/dockwidget/titlebar/label");
                setGeometry(sets_->value("geometry").toRect());
                setVisible(!sets_->value("hidden").toBool());
            sets_->endGroup();
        }

        void __save_settings__(){
            QSettings* sets_ = kernel::settings::Program::get_settings();
            sets_->beginGroup("varlist/dockwidget/titlebar/label");
                sets_->setValue("geometry",geometry());
                sets_->setValue("hidden",isHidden());
            sets_->endGroup();
        }

        void __load_styles__(){
            if(kernel::settings::Program::get_theme() == Themes::Dark)
                setPalette(Themes::Palette::get());
            else setPalette(Themes::LightStyle().palette());
        }
    };

    QLayout* common_layout_;
    Label *label_var_list;
    CollapseButton *collapse_var_list;
    CloseButton *close_var_list;
};

class DockWidget:public QDockWidget, public Retranslatable{
    Q_OBJECT
public:
    DockWidget(QMainWindow* parent);

    ~DockWidget(){
        __save_settings__();
    }

    virtual void retranslate() override;

private:
    Frame* frame_;
    TitleBar* titlebar_;
    QSize last_size;

    void __load_settings__(){
        QSettings* sets_ = kernel::settings::Program::get_settings();
        sets_->beginGroup("varlist/dockwidget");
            setGeometry(sets_->value("geometry").toRect());
            setVisible(!sets_->value("hidden").toBool());
        sets_->endGroup();
    }

    void __save_settings__(){
        QSettings* sets_ = kernel::settings::Program::get_settings();
        sets_->beginGroup("varlist/dockwidget");
            sets_->setValue("geometry",geometry());
            sets_->setValue("hidden",isHidden());
        sets_->endGroup();
    }

    void __load_styles__(){
        QSettings* sets_ = kernel::settings::Program::get_settings();
        if(kernel::settings::Program::get_theme() == Themes::Dark)
            setPalette(Themes::Palette::get());
        else setPalette(Themes::LightStyle().palette());
    }


public slots:
    void collapse(){
        if(frame_->isHidden()){
            //setFeatures(features()^QDockWidget::DockWidgetVerticalTitleBar);
            //titlebar_->setHorizontal();
            frame_->show();
            resize(last_size);
            //titlebar_->repaint();
        }
        else{
            last_size = size();
            //setFeatures(QDockWidget::DockWidgetVerticalTitleBar | features() );
            //titlebar_->setVertical();
            frame_->hide();
            //titlebar_->repaint();
        }
    }

    virtual void closeEvent(QCloseEvent *event) override{
        (void)event;
        if(qobject_cast<QMainWindow*>(parentWidget())->dockWidgetArea(this)!=Qt::NoDockWidgetArea)
            qobject_cast<QMainWindow*>(parentWidget())->removeDockWidget(this);
    }

    virtual void showEvent(QShowEvent *event) override{
        (void)event;
        if(parentWidget() && qobject_cast<QMainWindow*>(parentWidget())->dockWidgetArea(this)!=Qt::LeftDockWidgetArea)
            qobject_cast<QMainWindow*>(parentWidget())->addDockWidget(Qt::LeftDockWidgetArea,this);
    }
};

}
