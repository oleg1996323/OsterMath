#pragma once
#include <QWidget>
#include <PushButton.h>

struct INFO_NODE;
namespace dataview{
class LinkViewedNodes:public QWidget{
    Q_OBJECT
public:
    LinkViewedNodes(QWidget* parent):QWidget(parent){}

    void add_button(INFO_NODE*);
private:
    std::vector<PushButton> sequence_button_;
};

}
