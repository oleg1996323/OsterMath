#pragma once
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>

class Node;
class INFO_NODE;
namespace model::utilities {
class DelegateNodeEditor:public QWidget{
    Q_OBJECT
public:
    DelegateNodeEditor(QWidget* parent,std::unique_ptr<INFO_NODE>,bool);
    DelegateNodeEditor(QString,QWidget* parent,std::unique_ptr<INFO_NODE>,bool);
    void set_text(QString);
    void enable_btn(bool);
    void enable_editing(bool);

signals:
    void show_node(Node*,size_t);
private:
    //TODO connect with ExpressionTextEdit
    QPushButton* btn_view_node_;
    QLineEdit* expr_edit_;
    std::unique_ptr<INFO_NODE> info_;
};
}
