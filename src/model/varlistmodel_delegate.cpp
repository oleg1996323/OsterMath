#include "model/varlistmodel_delegate.h"

#include <qglobal.h>
#include <QMetaType>
#include <QVariant>
#include <QModelIndex>
#include <QLineEdit>
#include <QStringView>
#include <QDebug>
#include "model/exception/exception.h"
#include "model/varlistmodel.h"

namespace model{

VariablesDelegate::VariablesDelegate(QWidget* obj):
    QStyledItemDelegate(obj)
{}

QWidget* VariablesDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    if(index.isValid()){
        switch (index.column()){
        case (int)HEADER::NAME:{
            QLineEdit* line_name = new QLineEdit(index.data(Qt::DisplayRole).toString(),parent);
            line_name->setEnabled(true);
            return line_name;
        }
            break;
        case (int)HEADER::TYPE:{
            if(index.model()->rowCount()-1>index.row()){
                QComboBox *cb_types = new QComboBox(parent);
                cb_types->addItems(QStringList(variables::names_of_types));
                cb_types->setEditable(false);
                return cb_types;
            }
            break;
        }
        case (int)HEADER::EXPRESSION:
            if(index.model()->rowCount()-1>index.row()){
                QLineEdit* line_expr = new QLineEdit(parent);
                return line_expr;
            }
            break;
        case (int)HEADER::VALUE:
            return nullptr;
            break;
        case (int)HEADER::REMARK:
            if(index.model()->rowCount()-1>index.row()){
                QLineEdit* line_expr = new QLineEdit(parent);
                return line_expr;
            }
            break;
        }
    }
    return nullptr;
}

void VariablesDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    //if var is undef, then type can be modified
    QString value = 0;
    if(index.isValid()){
        switch (index.column()){
        case (int)HEADER::NAME:{
            QLineEdit* line_name = static_cast<QLineEdit*>(editor);
            line_name->setText(index.data(Qt::DisplayRole).toString());
        }
            break;
        case (int)HEADER::TYPE:{
            QComboBox *cb_types = static_cast<QComboBox*>(editor);
            if(index.model()->rowCount()-1>index.row()){
                //cb_types->setCurrentIndex((int)vars_.at(index.row())->type());
                qDebug()<<cb_types->currentIndex();
                if(*reinterpret_cast<TYPE_VAL*>(index.internalPointer())!=TYPE_VAL::UNKNOWN){
                    cb_types->setEnabled(false);
                    cb_types->setStyleSheet ("QComboBox::drop-down {border-width: 0px;} QComboBox::down-arrow {image: url(noimg); border-width: 0px;}");
                }
                else {
                    cb_types->setEnabled(true);
                }
            }
            else{
                cb_types->setEnabled(false);
                cb_types->setStyleSheet ("QComboBox::drop-down {border-width: 0px;} QComboBox::down-arrow {image: url(noimg); border-width: 0px;}");
            }
            break;
        }
        case (int)HEADER::EXPRESSION:
            if(index.model()->rowCount()-1>index.row()){
                QLineEdit* line_expr = static_cast<QLineEdit*>(editor);
                line_expr->setText(index.data(Qt::DisplayRole).toString());
            }
            break;
        case (int)HEADER::VALUE:
            break;
        case (int)HEADER::REMARK:
            if(index.model()->rowCount()-1>index.row()){
                QLineEdit* line_note = static_cast<QLineEdit*>(editor);
                line_note->setText(index.data(Qt::DisplayRole).toString());
            }
            break;
        }
    }
}

void VariablesDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QString value = 0;
    if(index.isValid()){
        switch (index.column()){
        case (int)HEADER::NAME:{
            QLineEdit* line_name = static_cast<QLineEdit*>(editor);
            model->setData(index,line_name->text(),Qt::EditRole);
        }
            break;
        case (int)HEADER::TYPE:{
            QComboBox *cb_types = static_cast<QComboBox*>(editor);
            model->setData(index,QVariant::fromValue((TYPE_VAL)cb_types->currentIndex()),Qt::EditRole);
            break;
        }
        case (int)HEADER::EXPRESSION:
            if(index.model()->rowCount()-1>index.row()){
                QLineEdit* line_expr = static_cast<QLineEdit*>(editor);
                model->setData(index,line_expr->text(),Qt::EditRole);
            }
            break;
        case (int)HEADER::VALUE:
            break;
        case (int)HEADER::REMARK:
            if(index.model()->rowCount()-1>index.row()){
                QLineEdit* line_note = static_cast<QLineEdit*>(editor);
                line_note->setText(index.data(Qt::DisplayRole).toString());
            }
            break;
        }
    }
}

void VariablesDelegate::set_default_header_pos(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    //порядок колонок
    sets_->beginGroup("VarListTable/header");
    sets_->setValue("name",QVariant().fromValue(HEADER::NAME));
    sets_->setValue("type",QVariant().fromValue(HEADER::TYPE));
    sets_->setValue("value",QVariant().fromValue(HEADER::VALUE));
    sets_->setValue("expression",QVariant().fromValue(HEADER::EXPRESSION));
    sets_->setValue("remark",QVariant().fromValue(HEADER::REMARK));
    sets_->endGroup();
}

void VariablesDelegate::get_header_pos(){

}

void VariablesDelegate::__load_settings__(){

}

void VariablesDelegate::__save_settings__(){

}


}
