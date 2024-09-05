#pragma once
#include <QTableView>
#include <QActionGroup>
#include "model/nodeview_delegate.h"
#include "model/nodeview_header.h"
#include "model/nodeview_select.h"

namespace dataview{

class NodeData: public QTableView, public ObjectFromSettings{
    Q_OBJECT
    QMenu *fontMenu;
    QMenu *alignMenu;
    QMenu *insertRowMenu;
    QMenu *insertColumnMenu;
    QMenu *removeMenu;
    QActionGroup *alignmentGroup;
    QActionGroup *fontGroup;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *centerAlignAct;
    QAction *justifyAlignAct;
    QAction *insertRowBeforeAct;
    QAction *insertColumnBeforeAct;
    QAction *insertRowAfterAct;
    QAction *insertColumnAfterAct;
    QAction *removeRowAct;
    QAction *removeColumnAct;

    QAction *insertSomeRowsAct;
    QAction *insertSomeColumnsAct;
    QAction *removeSomeRowsAct;
    QAction *removeSomeColumnsAct;


public:
    NodeData(QWidget* parent);
    ~NodeData();

    virtual void contextMenuEvent(QContextMenuEvent* event) override;
private:
    void createMenus();
    void createActions();
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;

private slots:
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void bold_font();
    void italic_font();
    void left_align();
    void right_align();
    void center_align();
    void justify_align();
    void insert_row_before();
    void insert_column_before();
    void insert_row_after();
    void insert_column_after();
    void delete_row();
    void delete_column();
};
}
