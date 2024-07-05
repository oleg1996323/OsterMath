#include "model/dataview_delegate.h"
#include <QPaintDevice>
#include <QPainter>
#include <QPushButton>

namespace model{

QWidget* DataViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{

}

void DataViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{

}

void DataViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{

}

void DataViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const{
    // here we have active painter provided by caller
    // by the way - we can't use painter->save() and painter->restore()
    // methods cause we have to call painter->end() method before painting
    // the QWidget, and painter->end() method deletes
    // the saved parameters of painter
    // we have to save paint device of the provided painter to restore the painter
    // after drawing QWidget
    QPaintDevice* original_pdev_ptr = painter->device();
    // example of simple drawing (selection) before widget
    if (option.state & QStyle::StateFlag::State_Item)
        painter->fillRect(option.rect, option.palette.highlight());
    // creating local QWidget (that's why i think it should be fasted, cause we
    // don't touch the heap and don't deal with a QWidget except painting)
    QPushButton item_widget("...");
    // Setting some parameters for widget for example
    // spec. params
    // geometry
    item_widget.setGeometry(option.rect);
    // here we have to finish the painting of provided painter, cause
    //     1) QWidget::render(QPainter *,...) doesn't work with provided external painter
    //          and we have to use QWidget::render(QPaintDevice *,...)
    //          which creates its own painter
    //     2) two painters can't work with the same QPaintDevice at the same time
    painter->end();
    // rendering of QWidget itself
    item_widget.render(painter->device(), QPoint(option.rect.x(), option.rect.y()), QRegion(0, 0, option.rect.width(), option.rect.height()), QWidget::RenderFlag::DrawChildren);
    // starting (in fact just continuing) painting with external painter, provided
    // by caller
    painter->begin(original_pdev_ptr);
    // example of simple painting after widget
    painter->drawEllipse(0,0, 10,10);
}
}
