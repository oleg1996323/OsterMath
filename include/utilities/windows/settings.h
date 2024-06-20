#pragma once
#include <QComboBox>
#include <QAction>
#include <QGridLayout>
#include "windef.h"
#include "kernel/settings.h"
#include "utilities/layouts/primitive_layouts.h"

class Settings:public QDialog,public AbstractSubWindowInterface{
    Q_OBJECT
public:
    Settings(QWidget* parent){
        layout_ = new QGridLayout(this);
        std::function<void(const kernel::settings::LANG_DATA&)> procedure_change_lang=[parent](const kernel::settings::LANG_DATA& res_data)->void{
                        qobject_cast<BookMath*>(parent)->set_language(res_data); };
        layout_->addLayout(new layouts::LanguageChoose(this,
                                                       parent,
                                                       procedure_change_lang),1,1);
        //QDialog::setLayout();
//        setObjectName("main_settings_window");
//        langs_ = new QComboBox(this);
//        QAction* rus_ = QAction("Русский",langs_);

//        langs_->addAction();
    }

private:
    QComboBox* langs_;
    QGridLayout* layout_;
};
