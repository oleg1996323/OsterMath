#include "kernel/application.h"
#include "bookmath.h"

namespace kernel{

        Application::Application(int &argc, char** argv):
            QApplication(argc,argv){
            setOrganizationName("Oster-Industries");
            setApplicationName("OsterMath");
            __load_settings__();
        }

        Application::~Application(){
            __save_settings__();
        }

        BaseData* Application::get_active_sheet(){
            return active_sheet_;
        }

        DataPool* Application::get_active_pool(){
            return active_pool_;
        }

        BookMath* Application::get_active_book(){
            return active_book_ui_;
        }

        void Application::__save_settings__(){
            settings::Program::__save_settings__();
        }

        void Application::__load_settings__(){
            settings::Program::__load_settings__();
        }

        BaseData* Application::active_sheet_ = nullptr;
        DataPool* Application::active_pool_ = nullptr;
        BookMath* Application::active_book_ui_ = nullptr;
}
