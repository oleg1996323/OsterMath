#include "kernel/application.h"

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

        BaseData* Application::get_active_data(){
            return active_data_;
        }

        DataPool* Application::get_active_pool(){
            return active_pool_;
        }

        BookMath* Application::get_active_book(){
            return active_book_ui_;
        }

        model::Manager* Application::get_model_manager(){
            return manager;
        }

        void Application::set_active_data(BaseData* data){
            active_data_ = data;
        }

        void Application::set_active_pool(DataPool* pool){
            active_pool_ = pool;
        }

        void Application::set_active_book(BookMath* book){
            active_book_ui_ = book;
        }

        void Application::set_model_manager(model::Manager* m){
            manager = m;
        }

        void Application::set_language(const settings::LANG_DATA& lang){
            settings::Program::set_language(lang.lang_);
            emit language_changed();
        }

        void Application::__save_settings__(){
            settings::Program::__save_settings__();
        }

        void Application::__load_settings__(){
            settings::Program::__load_settings__();
        }

        void Application::set_variable_list_showed(bool b){
            settings::Program::set_variable_list_showed(b);
            emit variable_list_showed(b);
        }

        BaseData* Application::active_data_ = nullptr;
        DataPool* Application::active_pool_ = nullptr;
        BookMath* Application::active_book_ui_ = nullptr;
        model::Manager* Application::manager = nullptr;
}
