#pragma once
#include <QObject>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "kernel/def.h"

namespace dataview{

class Table;

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

public:
    Frame(QWidget* parent);

    virtual void retranslate() override;

signals:
    void search_in_model(const QString&);
private:
    Label *label_search_var_list;
    SearchLine *search_var_list;

    virtual void showEvent(QShowEvent* event) override{
        updateGeometry();
    }

};
}
