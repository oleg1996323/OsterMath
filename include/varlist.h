#pragma once

#include <QObject>
#include <QFrame>
#include <QWidget>
#include <QSplitter>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include "./ui_var_list.h"

class VariableBase;

class VarList : public QFrame
{
    Q_OBJECT
public:
    explicit VarList(QWidget *parent = nullptr);

    void insert_var(QStringView var);

    void erase_var(QStringView var_name);

    void refresh();

signals:

private:
    class VarListItem;
    class VarSearchLine;
    class VarSearchLabel;
};

class VarList::VarListItem:public QTableWidget{
public:
    VarListItem(QWidget* parent):QTableWidget(parent){
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
        __qtablewidgetitem->setBackground(QColor(222, 221, 218));
        setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        __qtablewidgetitem1->setFont(font3);
        __qtablewidgetitem1->setBackground(QColor(222, 221, 218));
        setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        __qtablewidgetitem2->setFont(font3);
        __qtablewidgetitem2->setBackground(QColor(222, 221, 218));
        setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (rowCount() < 1)
            setRowCount(1);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::Dense1Pattern);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        __qtablewidgetitem3->setForeground(brush);
        setItem(0, 0, __qtablewidgetitem3);
        setObjectName(QString::fromUtf8("table_var_list"));
        setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sizePolicy().hasHeightForWidth());
        setSizePolicy(sizePolicy3);
        setMouseTracking(true);
        setTabletTracking(true);
        setContextMenuPolicy(Qt::NoContextMenu);
        setAcceptDrops(false);
        setFrameShape(QFrame::Panel);
        setFrameShadow(QFrame::Plain);
        setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        setDragEnabled(false);
        setDragDropMode(QAbstractItemView::NoDragDrop);
        setAlternatingRowColors(false);
        setSelectionMode(QAbstractItemView::SingleSelection);
        setTextElideMode(Qt::ElideRight);
        setShowGrid(true);
        setGridStyle(Qt::CustomDashLine);
        setSortingEnabled(false);
        setCornerButtonEnabled(true);
        setRowCount(1);
        setHorizontalHeader();
    }

private:
    class VarListHeader;
};

#include <QSettings>

class VarList::VarListItem::VarListHeader:public QHeaderView{
public:
    VarListHeader(QWidget* parent):QHeaderView(Qt::Orientation::Horizontal,parent){
        setVisible(true);
        setCascadingSectionResizes(false);
        setDefaultSectionSize(150);
        setStretchLastSection(true);

    }
private:

};

class VarList::VarSearchLine:public QLineEdit{

};

class VarList::VarSearchLabel:public QLabel{
    VarSearchLabel(QWidget* parent):QLabel(parent){
        setObjectName(QString::fromUtf8("label_var_list"));
        setObjectName(QString::fromUtf8("label_var_list"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
        setSizePolicy(sizePolicy);
        setMaximumSize(QSize(2000, 20));
        setText(QCoreApplication::translate("Form", "\320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265", nullptr));
    }


};
