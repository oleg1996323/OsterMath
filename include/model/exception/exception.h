#include "exception/exception.h"
#include <QMessageBox>

namespace model{
    template<typename FUNC>
    exceptions::EXCEPTION_TYPE exception_handler(FUNC function,QWidget* caller=nullptr){
        try{
            function;
            return exceptions::NOEXCEPT;
        }
        catch(const exceptions::Exception& err){
            QMessageBox msg(QMessageBox::Warning,err.get_error(),err.get_prompt(),QMessageBox::Apply,caller);
            return err.type();
        }
    }
}
