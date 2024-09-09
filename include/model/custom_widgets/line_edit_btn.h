#pragma once
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QModelIndex>

class Node;
namespace model::utilities {
class DelegateNodeEditor:public QWidget{
    Q_OBJECT
public:
    DelegateNodeEditor(QWidget* parent,const QModelIndex&,bool);
    DelegateNodeEditor(QString,QWidget* parent,const QModelIndex&,bool);
    void set_text(QString);
    void enable_btn(bool);
    void enable_editing(bool);

signals:
    void show_node(Node*);
private:
    //TODO connect with ExpressionTextEdit
    QPushButton* btn_view_node_;
    QLineEdit* expr_edit_;
    const QModelIndex& index_;
};
}
