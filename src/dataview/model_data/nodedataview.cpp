#include "dataview/model_data/nodedataview.h"
#include "model/nodeview_model.h"
#include <QMenu>
#include <QDebug>
#include <QPoint>
#include <QModelIndex>
#include <QBitArray>
#include "model/def.h"
#include "dataview/model_data/aux_windows/insert_columns.h"
#include "dataview/model_data/aux_windows/insert_rows.h"
#include "model/nodeview_select.h"
#include "model/custom_widgets/line_edit_btn.h"

namespace dataview{
NodeData::NodeData(QWidget* parent):
    QTableView(parent),
    ObjectFromSettings(this)
{
    setObjectName("nodedataview");
    load_settings();
    setItemDelegate(new model::NodeViewDelegate(this));
    setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
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

    removeRowAct= new QAction(QObject::tr("Remove selected rows"),this);
    connect(removeRowAct, &QAction::triggered, this, &NodeData::delete_row);

    removeColumnAct= new QAction(QObject::tr("Remove selected columns"),this);
    connect(removeColumnAct, &QAction::triggered, this, &NodeData::delete_column);

    insertSomeRowsAct = new QAction(QObject::tr("Insert rows ..."),this);
    connect(insertSomeRowsAct,&QAction::triggered,[this](){
        aux_window_ = new InsertRows(selectedIndexes(),this);
        connect(aux_window_,&RowColumnInsertInterface::close,[this](){
            this->insert_some_rows(aux_window_->get_value());
        });
    });
    insertSomeColumnsAct = new QAction(QObject::tr("Insert columns ..."),this);
    connect(insertSomeColumnsAct,&QAction::triggered,[this](){
        aux_window_ = new InsertColumns(selectedIndexes(),this);
        connect(aux_window_,&RowColumnInsertInterface::close,[this](){
            this->insert_some_columns(aux_window_->get_value());
        });
    });
}

void NodeData::contextMenuEvent(QContextMenuEvent* event){
    Q_UNUSED(event);
    model::NodeView* m = qobject_cast<model::NodeView*>(model());
    INFO_NODE info = m->get_node();
    if(info.parent && info.id>=0 && info.node()){
        QMenu menu(this);

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
        if(model::NodeViewSelectionModel* sel = qobject_cast<model::NodeViewSelectionModel*>(selectionModel())){
            if(!sel->is_empty()){
                cutAct->setEnabled(true);
                copyAct->setEnabled(true);
                pasteAct->setEnabled(true);
                fontMenu->setEnabled(true);
                alignMenu->setEnabled(true);
                if(model::NodeView* m = qobject_cast<model::NodeView*>(model())){
                    if(sel->is_columns()){
                        if(m->get_columns_cached_count()-1==sel->first_index().column()){
                            insertColumnAfterAct->setEnabled(false);
                        }
                        else insertColumnAfterAct->setEnabled(true);
                        insertRowAfterAct->setEnabled(false);
                        insertRowBeforeAct->setEnabled(false);

                        insertRowMenu->setEnabled(false);
                        insertColumnMenu->setEnabled(true);
                        removeRowAct->setEnabled(false);
                        removeColumnAct->setEnabled(true);
                        removeMenu->setEnabled(true);
                    }
                    else if(sel->is_rows()){
                        if(m->get_rows_cached_count()-1==sel->first_index().row()){
                            insertRowAfterAct->setEnabled(false);
                        }
                        else insertRowAfterAct->setEnabled(true);
                        insertColumnAfterAct->setEnabled(false);
                        insertColumnBeforeAct->setEnabled(false);

                        insertRowMenu->setEnabled(true);
                        insertColumnMenu->setEnabled(false);
                        removeRowAct->setEnabled(true);
                        removeColumnAct->setEnabled(false);
                        removeMenu->setEnabled(true);
                    }
                    else if(sel->is_range()){
                        if(m->get_rows_cached_count()-1==sel->first_index().row()){
                            insertRowAfterAct->setEnabled(false);
                        }
                        else insertRowAfterAct->setEnabled(true);
                        if(m->get_columns_cached_count()-1==sel->first_index().column()){
                            insertColumnAfterAct->setEnabled(false);
                        }
                        else insertColumnAfterAct->setEnabled(true);

                        insertColumnBeforeAct->setEnabled(true);

                        insertRowMenu->setEnabled(true);
                        insertColumnMenu->setEnabled(true);
                        removeRowAct->setEnabled(true);
                        removeColumnAct->setEnabled(true);
                        removeMenu->setEnabled(true);
                    }
                    else{
                        insertRowMenu->setEnabled(false);
                        insertColumnMenu->setEnabled(false);
                        removeMenu->setEnabled(false);
                    }
                }
                else qFatal("Model nodeview implementation error (Item Model)");
            }
            else{
                cutAct->setEnabled(false);
                copyAct->setEnabled(false);
                pasteAct->setEnabled(false);
                fontMenu->setEnabled(false);
                alignMenu->setEnabled(false);
                insertRowMenu->setEnabled(false);
                insertColumnMenu->setEnabled(false);
                removeMenu->setEnabled(false);
            }
        }
        else qFatal("Model nodeview implementation error (Selection model");
        menu.exec(event->globalPos());
    }
}

void NodeData::keyPressEvent(QKeyEvent* event){
    if(model::NodeViewSelectionModel* sel = qobject_cast<model::NodeViewSelectionModel*>(selectionModel())){
        qDebug()<<event->key();
        if(event->key() == Qt::Key::Key_Enter || event->key()==Qt::Key::Key_Return){
            if(state()==EditingState){
                commitData(indexWidget(sel->currentIndex()));
                closeEditor(indexWidget(sel->currentIndex()),
                QAbstractItemDelegate::EndEditHint::NoHint);
                sel->next_from_selection();
            }
            else if(state()==NoState){
                sel->next_from_selection();
            }
            else QTableView::keyPressEvent(event);
        }
        else if(event->key() == Qt::Key::Key_Backspace){
            //erasing item
            QTableView::keyPressEvent(event);
        }
        else if(event->key() == Qt::Key::Key_Delete){
            edit(sel->currentIndex());
            if(model::utilities::DelegateNodeEditor* editor = qobject_cast<model::utilities::DelegateNodeEditor*>(indexWidget(sel->currentIndex()))){
                editor->set_text("");
                commitData(editor);
                closeEditor(editor,
                QAbstractItemDelegate::EndEditHint::NoHint);
            }
            else QTableView::keyPressEvent(event);
        }
        else if(!event->text().isEmpty() && event->text().at(0).isPrint()){
            if(state()!=EditingState){
                edit(sel->currentIndex());
                if(model::utilities::DelegateNodeEditor* editor = qobject_cast<model::utilities::DelegateNodeEditor*>(indexWidget(sel->currentIndex()))){
                    editor->set_text(event->text().front());
                    commitData(editor);
                }
                else
                    QTableView::keyPressEvent(event);
            }
            else QTableView::keyPressEvent(event);
        }
        else{
            qDebug()<<event->text();
            QTableView::keyPressEvent(event);
        }
    }
    else QTableView::keyPressEvent(event);
//    else if(event->key() == Qt::Key::Key_Down ||
//            event->key()==Qt::Key::Key_Up ||
//            event->key()==Qt::Key::Key_Left ||
//            event->key()==Qt::Key::Key_Right){
//        if(model::NodeViewSelectionModel* sel = qobject_cast<model::NodeViewSelectionModel*>(selectionModel())){
//            if(state()==EditingState){
//                commitData(indexWidget(sel->currentIndex()));
//                closeEditor(indexWidget(sel->currentIndex()),
//                QAbstractItemDelegate::EndEditHint::NoHint);
//                QTableView::keyPressEvent(event);
//            }
//            else if(state()==NoState)
//                QTableView::keyPressEvent(event);
//        }
//        else QTableView::keyPressEvent(event);
//    }

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
    QModelIndexList indexes = selectedIndexes();
}

void NodeData::insert_row_before(){
    insert_some_rows({1, true});
}

void NodeData::insert_row_after(){
    insert_some_rows({1, false});
}

void NodeData::delete_row(){
    QModelIndexList indexes = selectedIndexes();
    std::sort(indexes.begin(),indexes.end());
}

void NodeData::insert_column_before(){
    insert_some_columns({1, true});
}

void NodeData::insert_column_after(){
    insert_some_columns({1, false});
}

void NodeData::delete_column(){
    QModelIndexList indexes = selectedIndexes();
    std::sort(indexes.begin(),indexes.end());
}

void NodeData::insert_some_rows(std::pair<int,bool> args){
    QModelIndexList indexes = selectedIndexes();
    if(!indexes.empty()){
        std::sort(indexes.begin(),indexes.end());
        if(model::NodeView* m = qobject_cast<model::NodeView*>(model())){
            if(args.second)
                m->insert_row_before(indexes.begin()->row(),args.first);
            else m->insert_row_before(indexes.begin()->row()+1,args.first);
        }
    }
}

void NodeData::insert_some_columns(std::pair<int,bool> args){
    QModelIndexList indexes = selectedIndexes();
    if(!indexes.empty()){
        std::sort(indexes.begin(),indexes.end());
        if(model::NodeView* m = qobject_cast<model::NodeView*>(model())){
            if(args.second)
                m->insert_column_before(indexes.begin()->column(),args.first);
            else m->insert_column_before(indexes.begin()->column()+1,args.first);
        }
    }
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
