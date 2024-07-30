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
        label_ = new QLabel(QObject::tr("Language"), this);
        langs_ = new QComboBox(this);

        langs_->setContentsMargins(0,0,0,0);

        int combo_index = 0;
        for(const auto& res_data:settings::resource_langs){
            QAction* action = new QAction(QIcon(res_data.path),res_data.text,langs_);
            langs_->addItem(QIcon(res_data.path),res_data.text,QVariant::fromValue(res_data.lang_));
            if(kernel::settings::Program::get_language()==res_data.lang_)
                langs_->setCurrentIndex(combo_index);
            ++combo_index;
        }
        layout_ = new QGridLayout(this);
        layout_->addWidget(label_,0,0,1,1,Qt::AlignLeft);
        layout_->addWidget(langs_,0,1,1,1,Qt::AlignLeft);
        //layout_->addLayout(new layouts::LanguageChoose(this),1,1,1,1,Qt::AlignLeft);
        this->setLayout(layout_);
    }

    ~Settings(){
        emit closing(true);
    }

    virtual SUBWINDOWTYPES type() const override{
        return SUBWINDOWTYPES::SETTINGS;
    }

    virtual void closeEvent(QCloseEvent* event) override{
        Q_UNUSED(event);
        if(langs_->currentData().value<QLocale::Language>()!=kernel::settings::Program::get_language()){
            kernel::settings::Program::set_language(langs_->currentData().value<QLocale::Language>());
            emit qobject_cast<kernel::Application*>(QCoreApplication::instance())->language_changed();
        }
        emit closing(true);
    }

signals:
    void closing(bool);

private:
    QLabel* label_;
    QComboBox* langs_;
    QGridLayout* layout_;
};
}
}
