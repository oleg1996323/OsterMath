#pragma once
#include <QComboBox>
#include <QAction>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include "windef.h"
#include "kernel/settings.h"
#include "utilities/layouts/primitive_layouts.h"

namespace Book{
namespace SecondairyWindows{
class Settings:public QMainWindow,public AbstractSubWindowInterface{
    Q_OBJECT
public:
    Settings(QWidget* parent):QMainWindow(parent,Qt::Dialog){
        Build();
        this->show();
    }

    void Build(){
        this->setWindowTitle(QObject::tr("Settings"));
        using namespace kernel;
        lang_label_ = new QLabel(QObject::tr("Language"), this);
        langs_ = new QComboBox(this);
        style_label_ = new QLabel(QObject::tr("Style"),this);
        styles_ = new QComboBox(this);

        langs_->setContentsMargins(0,0,0,0);

        int combo_index = 0;
        for(const auto& res_data:settings::resource_langs){
            langs_->addItem(QIcon(res_data.path),res_data.text,QVariant::fromValue(res_data.lang_));
            if(kernel::settings::Program::get_language()==res_data.lang_)
                langs_->setCurrentIndex(combo_index);
            ++combo_index;
        }
        combo_index = 0;
        for(const auto& res_data:settings::resource_styles){
            styles_->addItem(res_data.text_,QVariant::fromValue(res_data.type_));
            if(kernel::settings::Program::get_theme()==res_data.type_)
                styles_->setCurrentIndex(combo_index);
            ++combo_index;
        }
        layout_ = new QGridLayout(this);
        layout_->addWidget(lang_label_,0,0,1,1,Qt::AlignLeft);
        layout_->addWidget(langs_,0,1,1,1,Qt::AlignLeft);
        layout_->addWidget(style_label_,1,0,1,1,Qt::AlignLeft);
        layout_->addWidget(styles_,1,1,1,1,Qt::AlignLeft);
        QWidget* central  = new QWidget(this);
        setCentralWidget(central);
        central->setLayout(layout_);
    }

    ~Settings(){
        emit closing(true);
    }

    virtual SUBWINDOWTYPES type() const override{
        return SUBWINDOWTYPES::SETTINGS;
    }

    virtual void closeEvent(QCloseEvent* event) override{
        Q_UNUSED(event);
        if(langs_->currentData().value<QLocale::Language>()!=kernel::settings::Program::get_language())
            kernel::settings::Program::set_language(langs_->currentData().value<QLocale::Language>());
        if(styles_->currentData().value<Themes::TYPE>()!=kernel::settings::Program::get_theme())
            kernel::settings::Program::set_theme(styles_->currentData().value<Themes::TYPE>());
        emit closing(true);
    }

signals:
    void closing(bool);

private:
    QLabel* lang_label_;
    QLabel* style_label_;
    QComboBox* langs_;
    QComboBox* styles_;
    QGridLayout* layout_;
};
}
}
