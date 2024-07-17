#include "dataview/variable_list/table.h"
#include "kernel/application.h"
#include "model/varlist_model.h"
#include "model/varlist_header.h"
#include "model/varlist_delegate.h"

#include <QDebug>

namespace dataview{
Table::Table(QWidget* parent):ObjectFromSettings(this){
    setObjectName("tableview_var_list");
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
}
