#pragma once
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>

class Node;
namespace model::utilities {
class DelegateNodeEditor:public QWidget{
    Q_OBJECT
public:
    DelegateNodeEditor(QWidget* parent,QModelIndex,bool);
    DelegateNodeEditor(QString,QWidget* parent,QModelIndex,bool);
    void set_text(QString);
    void enable_btn(bool);
    void enable_editing(bool);

signals:
    void show_node(Node*);
private:
    //TODO connect with ExpressionTextEdit
    QPushButton* btn_view_node_;
    QLineEdit* expr_edit_;
};
}
