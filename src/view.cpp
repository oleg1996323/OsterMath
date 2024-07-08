#include "view.h"

void View::show_variable_list(){
    if(!var_list_->isVisible()){
        var_list_->show();
    }
}
