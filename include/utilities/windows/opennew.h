#pragma once
#include "windef.h"


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
