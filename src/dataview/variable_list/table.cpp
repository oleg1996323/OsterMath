#include "dataview/variable_list/table.h"
#include "kernel/application.h"
#include "model/varlist_model.h"
#include "model/varlist_header.h"
#include "model/varlist_delegate.h"

namespace dataview{
Table::Table(QWidget* parent){
    va_list_ = new model::Variables(parent, kernel::Application::get_active_data());
    setModel(var_list_);
    setItemDelegate(new model::VariablesDelegate(this));
    model::VariablesHeader* header = new model::VariablesHeader(this);
    setHorizontalHeader(header);
    header->setModel(var_list_);
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

void Table::change_model(QAbstractItemModel* model){
    this->setModel(model);
}
}
