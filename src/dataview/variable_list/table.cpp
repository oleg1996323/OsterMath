#include "dataview/variable_list/table.h"
#include "kernel/application.h"
#include "model/varlist_model.h"
#include "model/varlist_header.h"
#include "model/varlist_delegate.h"
#include <QDebug>

namespace dataview{
Table::Table(QWidget* parent):ObjectFromSettings(this){
    setObjectName("tableview_var_list");
    QSizePolicy size_policy;
    size_policy.setRetainSizeWhenHidden(true);
    size_policy.setHorizontalPolicy(QSizePolicy::Expanding);
    size_policy.setVerticalPolicy(QSizePolicy::Expanding);
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    setSizePolicy(size_policy);
    load_settings();
    setItemDelegate(new model::VariablesDelegate(this));
    setHorizontalHeader(new model::VariablesHeader(this));
    /*assert(header->itemDelegate());
    if (columnCount() < 3)
        setColumnCount(3);
    QFont font3;
    font3.setFamily(QString::fromUtf8("Sans Serif"));
    font3.setPointSize(8);
    font3.setBold(true);
    font3.setWeight(75);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    __qtablewidgetitem->setFont(font3);
    setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    __qtablewidgetitem1->setFont(font3);
    setHorizontalHeaderItem(1, __qtablewidgetitem1);
    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
    __qtablewidgetitem2->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    __qtablewidgetitem2->setFont(font3);
    setHorizontalHeaderItem(2, __qtablewidgetitem2);
    if (rowCount() < 1)
        setRowCount(1);
    QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
    __qtablewidgetitem3->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
    setItem(0, 0, __qtablewidgetitem3);
    setObjectName(QString::fromUtf8("table_var_list"));
    setEnabled(true);
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy3.setRetainSizeWhenHidden(true);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy3);
    setMouseTracking(true);
    setTabletTracking(true);
    setAcceptDrops(false);
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Plain);
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
    setDragEnabled(false);
    setDragDropMode(QAbstractItemView::NoDragDrop);
    setAlternatingRowColors(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setShowGrid(true);
    setRowCount(1);
    horizontalHeader()->setVisible(true);
    horizontalHeader()->setCascadingSectionResizes(false);
    horizontalHeader()->setDefaultSectionSize(150);
    horizontalHeader()->setStretchLastSection(true);*/

}

Table::~Table(){
    save_settings();
}

void Table::change_model(QAbstractItemModel* model){
    this->setModel(model);
}

void Table::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
    //qDebug()<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}
void Table::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    sets_->endGroup();
}
void Table::__upload_fonts__(){

}
void Table::__upload_style__(){

}
void Table::__upload_language__(){
    retranslate();
}
void Table::__retranslate__(){

}

QSize Table::sizeHint() const{
    QSize sz = size();
    return sz;
}
//QSize Table::minimumSizeHint() const{
//    return {viewportSizeHint().height(),0};
//}

//QRect Table::visualRect(const QModelIndex &index) const{

//}
//QRegion Table::visualRegionForSelection(const QItemSelection &selection) const{

//}
//void Table::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags){

//}
//void Table::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint){
//    if (!index.isValid()
//            || (model()->parent(index) != rootIndex())
//            || isIndexHidden(index))
//            return;
//        QAbstractItemViewPrivate::Span span;
//        if (d->hasSpans())
//            span = d->span(index.row(), index.column());
//        // Adjust horizontal position
//        int viewportWidth = d->viewport->width();
//        int horizontalOffset = d->horizontalHeader->offset();
//        int horizontalPosition = d->horizontalHeader->sectionPosition(index.column());
//        int horizontalIndex = d->horizontalHeader->visualIndex(index.column());
//        int cellWidth = d->hasSpans()
//                        ? d->columnSpanWidth(index.column(), span.width())
//                        : d->horizontalHeader->sectionSize(index.column());
//        if (horizontalScrollMode() == QAbstractItemView::ScrollPerItem) {
//            bool positionAtLeft = (horizontalPosition - horizontalOffset < 0);
//            bool positionAtRight = (horizontalPosition - horizontalOffset + cellWidth > viewportWidth);
//            if (hint == PositionAtCenter || positionAtRight) {
//                int w = (hint == PositionAtCenter ? viewportWidth / 2 : viewportWidth);
//                int x = cellWidth;
//                while (horizontalIndex > 0) {
//                    x += columnWidth(d->horizontalHeader->logicalIndex(horizontalIndex-1));
//                    if (x > w)
//                        break;
//                    --horizontalIndex;
//                }
//            }
//            if (positionAtRight || hint == PositionAtCenter || positionAtLeft) {
//                int hiddenSections = 0;
//                if (d->horizontalHeader->sectionsHidden()) {
//                    for (int s = horizontalIndex; s >= 0; --s) {
//                        int column = d->horizontalHeader->logicalIndex(s);
//                        if (d->horizontalHeader->isSectionHidden(column))
//                            ++hiddenSections;
//                    }
//                }
//                horizontalScrollBar()->setValue(horizontalIndex - hiddenSections);
//            }
//        } else { // ScrollPerPixel
//            if (hint == PositionAtCenter) {
//                horizontalScrollBar()->setValue(horizontalPosition - ((viewportWidth - cellWidth) / 2));
//            } else {
//                if (horizontalPosition - horizontalOffset < 0 || cellWidth > viewportWidth)
//                    horizontalScrollBar()->setValue(horizontalPosition);
//                else if (horizontalPosition - horizontalOffset + cellWidth > viewportWidth)
//                    horizontalScrollBar()->setValue(horizontalPosition - viewportWidth + cellWidth);
//            }
//        }
//        // Adjust vertical position
//        int viewportHeight = d->viewport->height();
//        int verticalOffset = d->verticalHeader->offset();
//        int verticalPosition = d->verticalHeader->sectionPosition(index.row());
//        int verticalIndex = d->verticalHeader->visualIndex(index.row());
//        int cellHeight = d->hasSpans()
//                         ? d->rowSpanHeight(index.row(), span.height())
//                         : d->verticalHeader->sectionSize(index.row());
//        if (verticalPosition - verticalOffset < 0 || cellHeight > viewportHeight) {
//            if (hint == EnsureVisible)
//                hint = PositionAtTop;
//        } else if (verticalPosition - verticalOffset + cellHeight > viewportHeight) {
//            if (hint == EnsureVisible)
//                hint = PositionAtBottom;
//        }
//        if (verticalScrollMode() == QAbstractItemView::ScrollPerItem) {
//            if (hint == PositionAtBottom || hint == PositionAtCenter) {
//                int h = (hint == PositionAtCenter ? viewportHeight / 2 : viewportHeight);
//                int y = cellHeight;
//                while (verticalIndex > 0) {
//                    int row = d->verticalHeader->logicalIndex(verticalIndex - 1);
//                    y += d->verticalHeader->sectionSize(row);
//                    if (y > h)
//                        break;
//                    --verticalIndex;
//                }
//            }
//            if (hint == PositionAtBottom || hint == PositionAtCenter || hint == PositionAtTop) {
//                int hiddenSections = 0;
//                if (d->verticalHeader->sectionsHidden()) {
//                    for (int s = verticalIndex; s >= 0; --s) {
//                        int row = d->verticalHeader->logicalIndex(s);
//                        if (d->verticalHeader->isSectionHidden(row))
//                            ++hiddenSections;
//                    }
//                }
//                verticalScrollBar()->setValue(verticalIndex - hiddenSections);
//            }
//        } else { // ScrollPerPixel
//            if (hint == PositionAtTop) {
//                verticalScrollBar()->setValue(verticalPosition);
//            } else if (hint == PositionAtBottom) {
//                verticalScrollBar()->setValue(verticalPosition - viewportHeight + cellHeight);
//            } else if (hint == PositionAtCenter) {
//                verticalScrollBar()->setValue(verticalPosition - ((viewportHeight - cellHeight) / 2));
//            }
//        }
//        d->setDirtyRegion(visualRect(index));

//}
//QModelIndex Table::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers){

//}
//bool Table::isIndexHidden(const QModelIndex &index) const{

//}
//QModelIndex Table::indexAt(const QPoint &point) const{

//}
//int Table::horizontalOffset() const{

//}
}
