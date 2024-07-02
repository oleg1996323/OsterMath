#include "data_view.h"
#include "kernel/settings.h"

VarExpressionView::VarExpressionView(QWidget* parent):QWidget(parent){
    this->setContentsMargins(0,0,0,0);
    layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(0,0,0,0);
    layout_->setSpacing(0);

    expression_ = new QTextEdit(this);
    expression_->setObjectName("expression"+parent->objectName());
    expression_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    expression_->setMinimumHeight(QFontMetrics(expression_->font()).height()+expression_->contentsMargins().top()+expression_->contentsMargins().bottom());
    expression_->setGeometry(pos().x(),pos().y(),width(),QFontMetrics(expression_->font()).height()+expression_->contentsMargins().top()+expression_->contentsMargins().bottom());
    qDebug()<<QFontMetrics(expression_->font()).height()+expression_->contentsMargins().top()+expression_->contentsMargins().bottom();

    formula_expl_ = new ExpressionButton(":booktool/icons/expr.png",this);
    formula_expl_->setObjectName("formula_expl"+parent->objectName());

    expand_collapse_expl_ = new CollapseButton(button_states::COLLAPSE_EXPAND_STATE::COLLAPSED,":common/common/expandexpr.png",":common/common/collapseexpr.png",this);
    expand_collapse_expl_->setObjectName("expand_collapse_expl"+parent->objectName());
    expand_collapse_expl_->setFixedSize(45,45);

    layout_->addWidget(formula_expl_);
    layout_->addWidget(expression_);
    layout_->addWidget(expand_collapse_expl_);
    layout_->setAlignment(formula_expl_,Qt::AlignTop);
    layout_->setAlignment(expression_,Qt::AlignTop);
    layout_->setAlignment(expand_collapse_expl_,Qt::AlignTop);

    layout_->setSizeConstraint(QHBoxLayout::SizeConstraint::SetMinimumSize);

    this->setLayout(layout_);
}

void VarExpressionView::expand_collapse(){
    expression_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
}

Sheets::Sheets(QWidget* parent):
    QTabWidget(parent)
{
    __load_settings__();
    for(int i=0;i<3;++i)
        add_default_sheet();
}

Sheets::Sheets(QWidget* parent, const QString& name):
    QTabWidget(parent)
{
    __load_settings__();
}

Sheets::~Sheets(){
    __save_settings__();
}

#include "data.h"
#include "model/dataviewmodel.h"

void Sheets::rename(const QString& name){
    kernel::Application::get_active_pool()->set_name(name.toStdString());
}

void Sheets::erase_sheet(const QString& name) noexcept{
    kernel::Application::get_active_pool()->erase(name.toStdString());
}

void Sheets::change_sheet_name(QString&& name, int tab_id){
    try{
        if(validator::BaseData::validate(name)==validator::Invalid)
            throw sheet::IncorrectName(tr("Недопустимое название листа").toStdString());
        for(int id = 0; id<count();++id)
            if(tabText(id)==name)
                throw sheet::AlreadyExist(tr("Лист с таким названием уже существует").toStdString());
        setTabText(tab_id,name);
    }
    catch(const std::logic_error& err){
        QMessageBox(QMessageBox::Icon::Critical,QObject::tr("Невозможно создать лист"), tr("Лист с таким названием уже существует"),QMessageBox::Ok,this);
    }
}

void Sheets::add_default_sheet(){
    QString new_name = tr("Лист"+QString::number(kernel::Application::get_active_pool()->size()+1).toUtf8());
    this->addTab(new QTableView(this),new_name);
}

void Sheets::set_new_model(QAbstractTableModel *model){
    qobject_cast<QTableView*>(widget(currentIndex()))->setModel(model);
}

void Sheets::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup("widget/sheetstab");
        this->setGeometry(sets_->value("geometry").toRect());
        setPalette(Themes::Palette::get());
    sets_->endGroup();
}

void Sheets::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup("sheetstab");
        sets_->setValue("geometry",geometry());
        setPalette(Themes::Palette::get());
    sets_->endGroup();
}

void VarDataView::open_var_data() const{

}
