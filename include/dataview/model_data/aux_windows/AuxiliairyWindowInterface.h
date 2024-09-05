#pragma once
#include <QWidget>
#include <QMainWindow>
#include <QDialogButtonBox>
#include <QDialog>
#include <QCloseEvent>
#include <QModelIndex>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

class QGridLayout;
class QLabel;
namespace dataview{
class AuxiliairyWindowInterface:public QMainWindow{
public:
    AuxiliairyWindowInterface(QWidget* parent):QMainWindow(parent, Qt::Widget | Qt::Tool){
        setAttribute(Qt::WA_DeleteOnClose);
        setWindowModality(Qt::WindowModality::WindowModal);
        btn_box_ = new QDialogButtonBox(QDialogButtonBox::Apply | QDialogButtonBox::Cancel,Qt::Horizontal);
        QObject::connect(btn_box_->button(QDialogButtonBox::Cancel),&QPushButton::pressed,this,&QMainWindow::close);
    }
    virtual ~AuxiliairyWindowInterface(){};
signals:
    void send_info_at_close(QVariant);
protected:
    QDialogButtonBox* btn_box_;
    virtual QVariant __get_value__() const = 0;
};
}
