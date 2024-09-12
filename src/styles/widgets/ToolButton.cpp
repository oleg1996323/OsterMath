#include "ToolButton.h"

ToolButton::ToolButton(const QString& res_path,QWidget* parent):PushButton(parent){
    setContentsMargins(0,0,0,0);
    setFixedSize(35,35);
    setIcon(paths::iconFromPath(path,QPixmap(res_path),size(),Qt::transparent));//TODO define in style
    setIconSize({width()-contentsMargins().left()-contentsMargins().right(),height()-contentsMargins().top()-contentsMargins().bottom()});
}
