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

class TitleBar:public QFrame, public Retranslatable, public ObjectFromSettings{
    Q_OBJECT
public:
    TitleBar(QWidget* parent);

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
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;

    class Label:public QLabel{
    public:
        Label(QWidget* parent);
        ~Label();
    };

    QLayout* common_layout_;
    Label *label_var_list;
    CollapseButton *collapse_var_list;
    CloseButton *close_var_list;
};
}
