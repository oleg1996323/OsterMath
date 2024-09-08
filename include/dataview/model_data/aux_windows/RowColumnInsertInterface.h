#pragma once
#include "AuxiliairyWindowInterface.h"

class QGridLayout;
namespace dataview{
class RowColumnInsertInterface:public AuxiliairyWindowInterface{
    Q_OBJECT
public:
    RowColumnInsertInterface(QWidget* parent);
    virtual ~RowColumnInsertInterface(){}
    using type_val = int;
    std::pair<int,bool> get_value() const;
protected:
    QSpinBox* spin_;
    QComboBox* before_after_;
    QGridLayout* main_layout_;
    QLabel* spin_label_;
    QLabel* combo_label_;
    QLabel* note_label_;
private:
    virtual QVariant __get_value__() const override;
};
}
