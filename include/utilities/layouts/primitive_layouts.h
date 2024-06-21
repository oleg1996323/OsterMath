#pragma once
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QAction>
#include "kernel/settings.h"
#include "kernel/application.h"
#include "bookmath.h"

namespace layouts{
    class LanguageChoose:public QHBoxLayout{
    public:
        LanguageChoose(QWidget* parent):QHBoxLayout(parent){
            label_ = new QLabel(QObject::tr("Language"), parent);
            langs_ = new QComboBox(parent);
            using namespace kernel;
            langs_->setContentsMargins(0,0,0,0);
            langs_->resize(30,30);

            for(const auto& res_data:settings::resource_langs){
                QAction* action = new QAction(QIcon(res_data.path),res_data.text);
                QObject::connect(action,&QAction::triggered,QApplication::instance(),[&res_data](){qobject_cast<Application*>(QApplication::instance())->set_language(res_data);});
                langs_->addAction(action);
            }
        }
    private:
        QLabel* label_;
        QComboBox* langs_;
    };
}
