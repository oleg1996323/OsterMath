#pragma once
#include "windef.h"

namespace Book{
namespace SecondairyWindows{

class CreateNewBook:public QMainWindow, public AbstractSubWindowInterface{
    Q_OBJECT
public:
    CreateNewBook(QWidget* parent):QMainWindow(parent){
        this->show();
    }

    ~CreateNewBook(){
        emit closing(true);
    }

    virtual SUBWINDOWTYPES type() const override{
        return SUBWINDOWTYPES::CREATE;
    }

private:

    virtual void closeEvent(QCloseEvent *event) override{
        (void)event;
        this->~CreateNewBook();
    }

signals:
    void closing(bool);
};
}
}
