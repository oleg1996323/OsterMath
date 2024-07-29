#pragma once
#include <QTabWidget>
#include <QHBoxLayout>
#include <QGroupBox>

class TabbedGroupedTools:public QTabWidget{
    Q_PROPERTY(Qt::Orientation orientation MEMBER orientation_ READ orientation WRITE setOrientation NOTIFY orientationChanged);
public:
    TabbedGroupedTools(QWidget* parent, Qt::Orientation = Qt::Horizontal);
    void set_box(QList<QGroupBox*> tools, QString name, int id = -1);
    void setLayoutsContentsMargins(int);
    void setGroupsMargins(int,int,int,int);
    void setGroupsMargins(QMargins);
    signals:
    void orientationChanged(Qt::Orientation);
private:
    QList<QGroupBox*> boxes_;
    Qt::Orientation orientation_;
};
