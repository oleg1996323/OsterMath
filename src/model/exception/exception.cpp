#include "model/exception/exception.h"

namespace model{
    exceptions::EXCEPTION_TYPE exception_handler(std::function<void()> function,QWidget* caller){
        try{
            function();
            return exceptions::NOEXCEPT;
        }
        catch(const exceptions::Exception& err){
            QMessageBox msg(QMessageBox::Warning,err.get_error(),err.get_prompt(),QMessageBox::Apply,caller);
            msg.show();
            return err.type();
        }
    }
}
