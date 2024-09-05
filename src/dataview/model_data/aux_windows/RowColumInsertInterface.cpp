#include "dataview/model_data/aux_windows/RowColumnInsertInterface.h"
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
using namespace std::string_literals;
namespace dataview{
RowColumnInsertInterface::RowColumnInsertInterface(QWidget* parent):
    AuxiliairyWindowInterface(parent){
    main_layout_ = new QGridLayout(this);
    QLabel* spin_label = new QLabel;
    QLabel* combo_label = new QLabel(QObject::tr("Before/after:"));
    QLabel* note_label_ = new QLabel;
    spin_ = new QSpinBox;
    spin_label->setBuddy(spin_);
    spin_->setAccelerated(true);
    spin_->setSingleStep(1);
    spin_->setValue(1);
    spin_->setMinimum(1);
    before_after_ = new QComboBox;
    combo_label->setBuddy(before_after_);

    before_after_->addItems({QObject::tr("Before"),QObject::tr("After")});
    before_after_->setCurrentIndex(0);

    main_layout_->addWidget(spin_label,0,0,Qt::AlignLeft);
    main_layout_->addWidget(spin_,0,1,Qt::AlignHCenter);
    main_layout_->addWidget(combo_label,1,0,Qt::AlignLeft);
    main_layout_->addWidget(before_after_,1,1,Qt::AlignLeft);
    main_layout_->addWidget(note_label_,2,0,1,2,Qt::AlignLeft);
    main_layout_->addWidget(btn_box_,3,0,1,2,Qt::AlignRight);
    setLayout(main_layout_);
}

int RowColumnInsertInterface::get_value() const{
    return __get_value__().value<int>();
}

QVariant RowColumnInsertInterface::__get_value__() const{
    if(spin_)
        return QVariant::fromValue(spin_->value());
    else {
        assert(false);
    }
}
}
