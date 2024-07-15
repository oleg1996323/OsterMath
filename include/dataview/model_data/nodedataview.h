#pragma once
#include <QTableView>
#include "model/nodeview_delegate.h"
#include "model/nodeview_header.h"

namespace dataview{

class NodeData: public QTableView, public ObjectFromSettings{
    Q_OBJECT
public:
    NodeData(QWidget* parent);
    ~NodeData();
private:
    virtual void __load_settings__() override;
    virtual void __save_settings__() override;
    virtual void __upload_fonts__() override;
    virtual void __upload_style__() override;
    virtual void __upload_language__() override;
};
}
