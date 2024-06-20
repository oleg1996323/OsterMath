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
        template<typename... T>
        LanguageChoose(QWidget* parent, QObject* slot_owner,std::function<void(T...)> slot){
            label_ = new QLabel(QObject::tr("Language"), parent);
            langs_ = new QComboBox(parent);
            using namespace kernel;
            langs_->setContentsMargins(0,0,0,0);
            langs_->resize(30,30);


            for(const auto& res_data:settings::resource_langs)
                langs_->addAction(QIcon(res_data.path),res_data.text,slot_owner, slot);
        }
    private:
        QLabel* label_;
        QComboBox* langs_;
    };
}
