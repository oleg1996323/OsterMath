#include "model/varlistmodel.h"

#include <qglobal.h>
#include <QMetaType>
#include <QVariant>
#include <QModelIndex>
#include <QLineEdit>
#include <QStringView>
#include <QDebug>

namespace model{

Variables::Variables(QObject* obj):
    QStyledItemDelegate(obj),
    QAbstractTableModel(obj)
{}

Variables::Variables(QObject* obj, BaseData* data_base):
    QStyledItemDelegate(obj),
    QAbstractTableModel(obj),
    data_base_(data_base)
{
    for(const auto& [var_name,var]:data_base->variables()){
        vars_.push_back({QString(),var.get(),var->type(),exceptions::EXCEPTION_TYPE::NOEXCEPT});
    }
}

int Variables::rowCount(const QModelIndex& parent = QModelIndex()) const {
    if(parent.isValid()){
        return 0;
    }
    return vars_.size()+1;
}

int Variables::columnCount(const QModelIndex &parent) const {
    //get from deserialized project settings
    return 5;
}

void Variables::addNewVariable(const QString& name){

}

void Variables::deleteVariable(const QString& name){

}

QVariant Variables::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal){
        if(section == (int)HEADER::NAME)
            return QObject::tr("Name");
        else if(section == (int)HEADER::TYPE)
            return QObject::tr("Type");
        else if(section == (int)HEADER::VALUE)
            return QObject::tr("Value");
        else if(section == (int)HEADER::EXPRESSION)
            return QObject::tr("Expression");
        else if(section == (int)HEADER::REMARK)
            return QObject::tr("Notes");
        else return QVariant();
    }
    else return QString::number(section+1);
}

QWidget* Variables::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    if(index.isValid()){
        switch (index.column()){
        case (int)HEADER::NAME:{
            QLineEdit* line_name = new QLineEdit(data(index,Qt::DisplayRole).toString(),parent);
            line_name->setEnabled(true);
            return line_name;
        }
            break;
        case (int)HEADER::TYPE:{
            if(vars_.size()>index.row()){
                QComboBox *cb_types = new QComboBox(parent);
                cb_types->addItems(QStringList(variables::names_of_types));
                cb_types->setEditable(false);
                return cb_types;
            }
            break;
        }
        case (int)HEADER::EXPRESSION:
            if(vars_.size()>index.row()){
                QLineEdit* line_expr = new QLineEdit(parent);
                return line_expr;
            }
            break;
        case (int)HEADER::VALUE:
            return nullptr;
            break;
        case (int)HEADER::REMARK:
            if(vars_.size()>index.row()){
                QLineEdit* line_expr = new QLineEdit(parent);
                return line_expr;
            }
            break;
        }
    }
    return nullptr;
}

void Variables::setEditorData(QWidget *editor, const QModelIndex &index) const{
    //if var is undef, then type can be modified
    QString value = 0;
    if(index.isValid()){
        switch (index.column()){
        case (int)HEADER::NAME:{
            QLineEdit* line_name = static_cast<QLineEdit*>(editor);
            line_name->setText(data(index,Qt::DisplayRole).toString());
        }
            break;
        case (int)HEADER::TYPE:{
            QComboBox *cb_types = static_cast<QComboBox*>(editor);
            if(vars_.size()>index.row()){
                //cb_types->setCurrentIndex((int)vars_.at(index.row())->type());
                qDebug()<<cb_types->currentIndex();

                if(vars_.at(index.row()).type_!=TYPE_VAL::UNKNOWN){
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
            if(vars_.size()>index.row()){
                QLineEdit* line_expr = static_cast<QLineEdit*>(editor);
                line_expr->setText(data(index,Qt::DisplayRole).toString());
            }
            break;
        case (int)HEADER::VALUE:
            break;
        case (int)HEADER::REMARK:
            if(vars_.size()>index.row()){
                QLineEdit* line_note = static_cast<QLineEdit*>(editor);
                line_note->setText(data(index,Qt::DisplayRole).toString());
            }
            break;
        }
    }
}

void Variables::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
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
            if(vars_.size()>index.row()){
                QLineEdit* line_expr = static_cast<QLineEdit*>(editor);
                QString var_expr = QString("VAR(!('%1')#%2)").arg(data_base_->name().data()).arg(vars_.at(index.row()).var_->name().data());
                std::stringstream stream;
                qDebug()<<var_expr<<line_expr->text();
                var_expr+=line_expr->text();
                qDebug()<<var_expr;
                model->setData(index,var_expr,Qt::EditRole);
            }
            break;
        case (int)HEADER::VALUE:
            break;
        case (int)HEADER::REMARK:
            if(vars_.size()>index.row()){
                QLineEdit* line_note = static_cast<QLineEdit*>(editor);
                line_note->setText(data(index,Qt::DisplayRole).toString());
            }
            break;
        }
    }
}

QVariant Variables::data(const QModelIndex& index,int nRole) const {
    if(!index.isValid()){
        return QVariant();
    }
    if(index.row()<0 || index.row()>vars_.size()){
        return QVariant();
    }

    if(nRole == Qt::DisplayRole){
        if(index.row()<vars_.size()){
            switch (index.column()){
            case (int)HEADER::NAME:{
                return QString::fromStdString(vars_.at(index.row()).var_->name());
                break;
            }
            case (int)HEADER::TYPE:{
                return variables::names_of_types[(int)vars_.at(index.row()).type_];
                break;
            }
            case (int)HEADER::EXPRESSION:{
                return QString::fromStdString(vars_.at(index.row()).var_->text());
                break;
            }
            case (int)HEADER::VALUE:{
                if(!vars_.at(index.row()).err_){
                    std::stringstream stream;
                    vars_.at(index.row()).var_->set_stream(stream);
                    vars_.at(index.row()).var_->print_result();
                    return QString::fromStdString(stream.str());
                }
                else return QString::fromUtf8(exceptions::get_except_abbr(vars_.at(index.row()).err_));
                break;
            }
            case (int)HEADER::REMARK:{
                return vars_.at(index.row()).note_;
                break;
            }
            default:
                return QVariant();
                break;
            }
        }
        else return QVariant();
    }
    else if(nRole == Qt::EditRole){
        return QVariant();
    }
    else return QVariant();
}

bool Variables::setData(const QModelIndex& index, const QVariant& value, int nRole) {
    if(index.isValid()){
        //for names
        if(nRole == Qt::EditRole){
            switch (index.column()){
            case (int)HEADER::NAME:{
                if(!value.isNull()){
                    if(value.toString()!=""){
                        if(!data_base_->exists(value.toString().toStdString())){
                            if(vars_.size()==index.row()){
                                vars_.push_back({QString(),data_base_->add_variable(std::move(value.toString().toStdString())).get(),TYPE_VAL::UNKNOWN,exceptions::EXCEPTION_TYPE::NOEXCEPT});
                                insertRow(rowCount());
                            }
                            else
                                data_base_->rename_var(vars_.at(index.row()).var_->name(),value.toString().toStdString());
                        }
                        return true;
                    }
                    else{
                        if(!vars_.empty()){
                            QString name_var = data(index,Qt::DisplayRole).toString();
                            data_base_->erase(name_var.toStdString());
                            assert(QMetaType::isRegistered(QMetaType::type("std::string")));
                            assert(!data_base_->exists(data(index,Qt::DisplayRole).toString().toStdString()));
                            removeRow(index.row());
                        }
                        return true;
                    }
                }
                return false;
                break;
            }
            case (int)HEADER::TYPE:{
                switch(value.value<TYPE_VAL>()){
                case TYPE_VAL::UNKNOWN:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::UNKNOWN;
                    }
                    return true;
                    break;
                case TYPE_VAL::ARRAY:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::ARRAY;
                        //vars_.at(index.row())->node()->insert(std::make_shared<ArrayNode>());
                    }
                    return true;
                    break;
                case TYPE_VAL::NUMERIC_ARRAY:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::NUMERIC_ARRAY;
                    }
                    return true;
                    break;
                case TYPE_VAL::STRING_ARRAY:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::STRING_ARRAY;
                    }
                    return true;
                    break;
                case TYPE_VAL::STRING:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::STRING;
                    }
                    return true;
                    break;
                case TYPE_VAL::VALUE:
                    if(vars_.at(index.row()).var_->type()!=(TYPE_VAL)value.toInt()){
                        vars_.at(index.row()).var_->node()->release_childs();
                        vars_.at(index.row()).type_ = TYPE_VAL::VALUE;
                    }
                    return true;
                    break;
                default:
                    return true;
                    break;
                }
                break;
            }
            case (int)HEADER::EXPRESSION:{
                std::stringstream stream;
                stream<<value.toString().toStdString();
                data_base_->setstream(stream);
                vars_.at(index.row()).err_ = exception_handler([&](){
                    data_base_->read_new();
                });
                if(vars_.at(index.row()).err_)
                    vars_.at(index.row()).err_=exception_handler([&](){
                        vars_.at(index.row()).var_->refresh();
                    });
                return true;
                break;
            }
            case (int)HEADER::VALUE:{
                return true;
                break;
            }
            case (int)HEADER::REMARK:{
                return true;
                break;
            }
            }
        }
    }
    return false;
}

Qt::ItemFlags Variables::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return (index.isValid())?(flags | Qt::ItemIsEditable):flags;
}

bool Variables::insertRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) {
    if(parent.isValid())
        return false;

    beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);
    endInsertRows();
    return true;
}

bool Variables::insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) {
    if(parent.isValid())
        return false;
    return true;
    //        beginInsertColumns(QModelIndex(),column,column+count-1);
    //        for(int i = 0;i<count;++i){

    //        }

}

bool Variables::removeRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) {
    if(parent.isValid())
        return false;

    beginRemoveRows(QModelIndex(),nRow,nRow+nCount-1);
    for(int i = 0; i<nCount; ++i){
        vars_.erase(vars_.begin()+nRow);
    }
    endRemoveRows();
    return true;
}

void Variables::set_default_header_pos(){
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

void Variables::get_header_pos(){

}

void Variables::__load_settings__(){

}

void Variables::__save_settings__(){

}


}
