#pragma once
#include <QFrame>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include "utilities/custom_widgets/buttons.h"
#include "kernel/application.h"

namespace dataview{

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
}
