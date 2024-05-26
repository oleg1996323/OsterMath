#pragma once
#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QStringList>
#include <QList>
#include "def.h"

enum class SUBWINDOWTYPES{
    CREATE,
    OPEN,
    SAVEAS
};

class AbstractSubWindowInterface{
public:
    virtual ~AbstractSubWindowInterface(){}

    virtual SUBWINDOWTYPES type() const = 0;
protected:

};

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

class OpenNewBook:public QFileDialog,public AbstractSubWindowInterface{
    Q_OBJECT
public:
    OpenNewBook(QWidget* parent):QFileDialog(parent){
        Build();
        this->show();
    }

    void Build(){
        QFileDialog::connect(this,&QFileDialog::rejected,this,&OpenNewBook::Cancel);
        this->setNameFilters(QStringList(QList<QString>(format_.begin(),format_.end())));
        this->setDirectory(QDir::homePath());
    }

    ~OpenNewBook(){
        emit closing(true);
    }

    virtual SUBWINDOWTYPES type() const override{
        return SUBWINDOWTYPES::OPEN;
    }

signals:
    void closing(bool);

private:
    virtual void closeEvent(QCloseEvent *event) override{
        (void)event;
        this->~OpenNewBook();
    }
private slots:
    void Cancel(){
        this->~OpenNewBook();
    }
};

