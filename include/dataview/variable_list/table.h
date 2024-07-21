#pragma once
#include <QAbstractItemView>
#include <QTableView>
#include "kernel/def.h"
#include "arithmetic_types.h"
#include "model/varlist_delegate.h"
#include "model/varlist_header.h"

namespace model{
class Variables;
}

namespace dataview{

class Table:public QTableView, public Retranslatable, public ObjectFromSettings{
public:
    Table(QWidget* parent);
    ~Table();

public slots:
    void change_model(QAbstractItemModel*);

private:
    model::VariablesDelegate* var_list_delegate_;
    model::VariablesHeader* var_list_header_;

//    virtual QRect visualRect(const QModelIndex &index) const override;
//    virtual QRegion visualRegionForSelection(const QItemSelection &selection) const override;
//    virtual void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags) override;
//    virtual void scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint = EnsureVisible) override;
//    virtual QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
//    virtual bool isIndexHidden(const QModelIndex &index) const override;
//    virtual QModelIndex indexAt(const QPoint &point) const override;
//    virtual int horizontalOffset() const override;

    //virtual QSize viewportSizeHint() const override;
    virtual QSize sizeHint() const override;
    //virtual QSize minimumSizeHint() const override;
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
    virtual void __retranslate__() override;
};
}
