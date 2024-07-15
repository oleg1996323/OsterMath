#pragma once
#include <QObject>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "kernel/def.h"
#include "model/varlist_model.h"

namespace dataview{

class Table;

class Frame:public QFrame, public Retranslatable{
    Q_OBJECT
public:
    Frame(QWidget* parent);
public slots:

    void set_model(model::Variables*);

signals:
    void search_in_model(const QString&);
private:
    QLabel *label_search_var_list;
    QLineEdit *search_var_list;
    model::Variables* var_list_model_ = nullptr;

    virtual void showEvent(QShowEvent* event) override{
        updateGeometry();
    }
    virtual void __retranslate__() override;

    void __define_search_line__();
    void __define_label__();
    void __define_frame__();

};
}
