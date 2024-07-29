#pragma once
#include <QSplitter>
#include <QObject>
#include "dataview/sheets.h"
#include "dataview/expression_view.h"
#include "kernel/def.h"

namespace dataview{

class DataViewSplit:public QSplitter, public ObjectFromSettings{
    Q_OBJECT
public:
    DataViewSplit(QWidget* parent);

    Sheets* sheets() const;

private:

    void __define_view__();

    void __define_signals_slots__();

    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;

    Sheets* sheets_;
    VarExpressionView* expression_view_;
};
}
