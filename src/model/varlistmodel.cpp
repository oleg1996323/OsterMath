#include "model/varlistmodel.h"
#include "arithmetic_types.h"
#include <qglobal.h>
#include <QModelIndex>

Q_DECLARE_METATYPE(::TYPE_VAL)

namespace model{

static QList<QString> names_of_types = {
        QT_TRANSLATE_NOOP("ModelItemsTypes","Unknown"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","String array"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","Numeric array"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","Value"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","String"),
        QT_TRANSLATE_NOOP("ModelItemsTypes","Array")
    };

    Variables::Variables(QObject* obj):
        QStyledItemDelegate(obj),
        QAbstractTableModel(obj)
    {}

    Variables::Variables(QObject* obj, BaseData* data_base):
        QStyledItemDelegate(obj),
        QAbstractTableModel(obj),
        data_base_(data_base)
    {
        for(const auto& [var_name,var]:data_base->variables())
            vars_.push_back(var.get());
    }

    void Variables::addNewVariable(const QString& name){

    }

    void Variables::deleteVariable(const QString& name){

    }

    QWidget* Variables::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        QComboBox *cb_types = new QComboBox(parent);
        cb_types->setEditable(true);
        cb_types->addItems(QStringList(names_of_types));
        cb_types->setEditable(false);
        return cb_types;
    }

    void Variables::setEditorData(QWidget *editor, const QModelIndex &index) const{
        //if var is undef, then type can be modified
        QString value = 0;
        if(index.isValid() && index.column()<vars_.size()){
            value = names_of_types[(int)vars_.at(index.row())->type()];

            QComboBox *cb_types = static_cast<QComboBox*>(editor);
            if(vars_.at(index.row())->type()!=TYPE_VAL::UNKNOWN){
                cb_types->setEditable(false);
                cb_types->setEnabled(false);
            }
            else {

                cb_types->setEnabled(true);
            }

            cb_types->setCurrentIndex((int)vars_.at(index.row())->type());
        }
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
        else return QString::number(section);
    }

     QVariant Variables::data(const QModelIndex& index,int nRole) const {
        if(!index.isValid()){
            return QVariant();
        }
        if(index.row()<0 || index.row()>=vars_.size()){
            return QVariant();
        }

        if(index.column()==0)
            return (nRole==Qt::DisplayRole || nRole==Qt::EditRole)
                    ? QString::fromStdString(std::string(vars_.at(index.row())->name()))
                    : QVariant();
        else return QVariant();
    }

     bool Variables::setData(const QModelIndex& index, const QVariant& value, int nRole) {
        if(index.isValid() && nRole == Qt::EditRole){
            //for names
            if(index.column()==(int)HEADER::NAME){
                if(vars_.size()==index.row()){
                    vars_.push_back(data_base_->add_variable(value.value<std::string>()).get());
                    setData(index.siblingAtColumn((int)HEADER::NAME),names_of_types[(int)vars_.at(index.row())->type()],nRole);
                }
                else
                    data_base_->rename_var(std::string(vars_.at(index.row())->name()),value.value<std::string>());
            }
            //for types
            else if(index.column()==(int)HEADER::NAME){
                if(vars_.size()>=index.row()){
                    switch(value.value<TYPE_VAL>()){
                    case TYPE_VAL::UNKNOWN:
                        vars_.at(index.row())->node()->release_childs();
                        break;
                    case TYPE_VAL::STRING:{
                        //vars_.at(index.row())->node()->insert(std::make_shared<StringNode>());
                        break;
                    }
                    case TYPE_VAL::VALUE:{
                        vars_.at(index.row())->node()->insert(std::make_shared<ValueNode>(0));
                        break;
                    }
                    case TYPE_VAL::NUMERIC_ARRAY:{
                        break;
                    }
                    case TYPE_VAL::STRING_ARRAY:{
                        break;
                    }
                    case TYPE_VAL::ARRAY:{
                        break;
                    }
                    default:{
                        break;
                    }


                    data_base_->get(data(index.siblingAtColumn((int)HEADER::TYPE),Qt::DisplayRole).value<std::string>());
                }
            }
            else
                data_base_->rename_var(std::string(vars_.at(index.row())->name()),value.value<std::string>());
            emit dataChanged(index,index);
            return true;
            }
        }
        return false;
    }

     int Variables::rowCount(const QModelIndex& parent = QModelIndex()) const {
        if(parent.isValid()){
            return 0;
        }
        return vars_.size();
    }

     int Variables::columnCount(const QModelIndex &parent) const {
        if(parent.isValid()){
            return 0;
        }
        return 5;
    }

     Qt::ItemFlags Variables::flags(const QModelIndex& index) const {
        Qt::ItemFlags flags = QAbstractTableModel::flags(index);
        return (index.isValid())?(flags | Qt::ItemIsEditable):flags;
    }

     bool Variables::insertRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) {
        if(parent.isValid())
            return false;

        beginInsertRows(QModelIndex(),nRow,nRow+nCount-1);
        for(int i = 0; i<nCount; ++i){
            vars_.insert(nRow,0);
        }
        endInsertRows();
        return true;
    }

     bool Variables::insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) {
        if(parent.isValid())
            return false;
//        beginInsertColumns(QModelIndex(),column,column+count-1);
//        for(int i = 0;i<count;++i){

//        }
    }

     bool Variables::removeRows(int nRow, int nCount, const QModelIndex& parent = QModelIndex()) {
        if(parent.isValid())
            return false;

        beginRemoveRows(QModelIndex(),nRow,nRow+nCount-1);
        for(int i = 0; i<nCount; ++i){
            vars_.removeAt(nRow);
        }
        endRemoveRows();
        return true;
    }

    void Variables::set_default_header_pos(){
        QSettings* sets_ = kernel::settings::Program::get_settings();
        //порядок колонок
        sets_->beginGroup("VarListTable/header");
            sets_->setValue("name",HEADER::NAME);
            sets_->setValue("type",HEADER::TYPE);
            sets_->setValue("value",HEADER::VALUE);
            sets_->setValue("expression",HEADER::EXPRESSION);
            sets_->setValue("remark",HEADER::REMARK);
        sets_->endGroup();
    }

    void Variables::get_header_pos(){

    }

    void Variables::__load_settings__(){

    }

    void Variables::__save_settings__(){

    }


}
