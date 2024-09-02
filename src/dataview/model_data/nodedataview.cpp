#include "dataview/model_data/nodedataview.h"
#include "model/nodeview_model.h"
#include <QMenu>
#include <QDebug>

namespace dataview{
NodeData::NodeData(QWidget* parent):
    QTableView(parent),
    ObjectFromSettings(this)
{
    setObjectName("nodedataview");
    load_settings();
    setItemDelegate(new model::NodeViewDelegate(this));
    setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    setSelectionModel(new model::NodeViewSelectionModel);
    setHorizontalHeader(new model::NodeViewHeader(this));
    setContentsMargins(5,0,5,0);
    createActions();
    createMenus();
}

NodeData::~NodeData(){
    save_settings();
}

void NodeData::createMenus(){
    fontMenu = new QMenu(QObject::tr("Font"),this);
    fontMenu->addAction(boldAct);
    fontMenu->addAction(italicAct);
    alignMenu = new QMenu(QObject::tr("Alignment"),this);
    alignMenu->addAction(leftAlignAct);
    alignMenu->addAction(rightAlignAct);
    alignMenu->addAction(centerAlignAct);
    alignMenu->addAction(justifyAlignAct);
    insertRowMenu = new QMenu(QObject::tr("Insert row"),this);
    insertRowMenu->addAction(insertRowBeforeAct);
    insertRowMenu->addAction(insertRowAfterAct);
    insertColumnMenu = new QMenu(QObject::tr("Insert column"),this);
    insertColumnMenu->addAction(insertColumnBeforeAct);
    insertColumnMenu->addAction(insertColumnAfterAct);
    removeMenu = new QMenu(QObject::tr("Remove"),this);
    removeMenu->addAction(removeRowAct);
    removeMenu->addAction(removeColumnAct);
}

void NodeData::createActions()
{

    undoAct = new QAction(QObject::tr("Undo"),this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, &QAction::triggered, this, &NodeData::undo);

    redoAct= new QAction(QObject::tr("Redo"),this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, &QAction::triggered, this, &NodeData::redo);

    cutAct= new QAction(QObject::tr("Cut"),this);
    cutAct->setShortcuts(QKeySequence::Cut);
    connect(cutAct, &QAction::triggered, this, &NodeData::cut);

    copyAct= new QAction(QObject::tr("Copy"),this);
    copyAct->setShortcuts(QKeySequence::Copy);
    connect(copyAct, &QAction::triggered, this, &NodeData::copy);

    pasteAct= new QAction(QObject::tr("Paste"),this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    connect(pasteAct, &QAction::triggered, this, &NodeData::paste);

    fontGroup = new QActionGroup(this);
    boldAct= new QAction(QObject::tr("Bold"),this);
    boldAct->setShortcuts(QKeySequence::Bold);
    connect(boldAct, &QAction::triggered, this, &NodeData::bold_font);

    italicAct= new QAction(QObject::tr("Italic"),this);
    italicAct->setShortcuts(QKeySequence::Italic);
    connect(italicAct, &QAction::triggered, this, &NodeData::italic_font);


    alignmentGroup = new QActionGroup(this);
    leftAlignAct= new QAction(QObject::tr("Left"),this);
    connect(leftAlignAct, &QAction::triggered, this, &NodeData::left_align);
    rightAlignAct= new QAction(QObject::tr("Right"),this);
    connect(rightAlignAct, &QAction::triggered, this, &NodeData::right_align);
    centerAlignAct= new QAction(QObject::tr("Center"),this);
    connect(centerAlignAct, &QAction::triggered, this, &NodeData::center_align);
    justifyAlignAct= new QAction(QObject::tr("Justify"),this);
    connect(justifyAlignAct, &QAction::triggered, this, &NodeData::justify_align);

    leftAlignAct->setChecked(true);

    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(centerAlignAct);
    alignmentGroup->addAction(justifyAlignAct);

    insertRowBeforeAct= new QAction(QObject::tr("Before"),this);
    connect(insertRowBeforeAct, &QAction::triggered, this, &NodeData::insert_row_before);

    insertRowAfterAct= new QAction(QObject::tr("After"),this);
    connect(insertRowAfterAct, &QAction::triggered, this, &NodeData::insert_row_after);

    insertColumnBeforeAct= new QAction(QObject::tr("Before"),this);
    connect(insertColumnBeforeAct, &QAction::triggered, this, &NodeData::insert_column_before);

    insertColumnAfterAct= new QAction(QObject::tr("After"),this);
    connect(insertColumnAfterAct, &QAction::triggered, this, &NodeData::insert_column_after);

    removeRowAct= new QAction(QObject::tr("Remove row"),this);
    connect(removeRowAct, &QAction::triggered, this, &NodeData::delete_row);

    removeColumnAct= new QAction(QObject::tr("Remove column"),this);
    connect(removeColumnAct, &QAction::triggered, this, &NodeData::delete_column);
}

void NodeData::contextMenuEvent(QContextMenuEvent* event){
    Q_UNUSED(event);
    model::NodeView* m = qobject_cast<model::NodeView*>(model());
    if(m->get_node()){
        QMenu menu(this);
        QModelIndexList indexes = selectedIndexes();
        if(!indexes.empty()){
            std::sort(indexes.begin(),indexes.end());
            if(model::NodeView* m = qobject_cast<model::NodeView*>(model())){
                if(m->get_rows_cached_count()-1==indexes.begin()->row()){
                    insertRowAfterAct->setEnabled(false);
                }
                else insertRowAfterAct->setEnabled(true);
                if(m->get_columns_cached_count()-1==indexes.begin()->column()){
                    insertColumnAfterAct->setEnabled(false);
                }
                else insertColumnAfterAct->setEnabled(true);
            }
        }
        menu.addAction(undoAct);
        menu.addAction(redoAct);
        menu.addAction(cutAct);
        menu.addAction(copyAct);
        menu.addAction(pasteAct);
        menu.addSeparator();
        menu.addMenu(insertRowMenu);
        menu.addMenu(insertColumnMenu);
        menu.addMenu(removeMenu);
        menu.addSeparator();
        menu.addMenu(fontMenu);
        menu.addMenu(alignMenu);
        menu.exec(event->globalPos());
    }
}

void NodeData::undo(){

}

void NodeData::redo(){

}

void NodeData::cut(){

}

void NodeData::copy(){

}

void NodeData::paste(){

}

void NodeData::bold_font(){

}

void NodeData::italic_font(){

}

void NodeData::left_align(){

}

void NodeData::right_align(){

}

void NodeData::center_align(){

}

void NodeData::justify_align(){

}

void NodeData::insert_row_before(){
    QModelIndexList indexes = selectedIndexes();
    if(!indexes.empty()){
        std::sort(indexes.begin(),indexes.end());
        if(model::NodeView* m = qobject_cast<model::NodeView*>(model())){
            m->insert_row_before(indexes.begin()->row(),1);
        }
    }
}

void NodeData::insert_row_after(){
    QModelIndexList indexes = selectedIndexes();
    if(!indexes.empty()){
        std::sort(indexes.begin(),indexes.end());
        if(model::NodeView* m = qobject_cast<model::NodeView*>(model())){
            if(m->get_rows_cached_count()-1!=indexes.begin()->row())
                m->insert_row_after(indexes.begin()->row()+1,1);
        }
    }
}

void NodeData::delete_row(){
    QModelIndexList indexes = selectedIndexes();
    std::sort(indexes.begin(),indexes.end());
}

void NodeData::insert_column_before(){
    QModelIndexList indexes = selectedIndexes();
    if(!indexes.empty()){
        std::sort(indexes.begin(),indexes.end());
        if(model::NodeView* m = qobject_cast<model::NodeView*>(model())){
            m->insert_column_before(indexes.begin()->column(),1);
        }
    }
}

void NodeData::insert_column_after(){
    QModelIndexList indexes = selectedIndexes();
    if(!indexes.empty()){
        std::sort(indexes.begin(),indexes.end());
        if(model::NodeView* m = qobject_cast<model::NodeView*>(model())){
            m->insert_column_after(indexes.begin()->column()+1,1);
        }
    }
}

void NodeData::delete_column(){
    QModelIndexList indexes = selectedIndexes();
    std::sort(indexes.begin(),indexes.end());
}

void NodeData::__load_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    restoreGeometry(sets_->value("geometry").toByteArray());
    //qDebug()<<"NodeData init geometry"<<geometry(); //размер инициализируется окном (надо исправить)
    sets_->endGroup();
}
void NodeData::__save_settings__(){
    QSettings* sets_ = kernel::settings::Program::get_settings();
    sets_->beginGroup(objectName());
    sets_->setValue("geometry",saveGeometry());
    //qDebug()<<"NodeData save geometry"<<geometry();
    sets_->endGroup();
}
void NodeData::__upload_fonts__(){

}
void NodeData::__upload_style__(){

}
void NodeData::__upload_language__(){

}

}
