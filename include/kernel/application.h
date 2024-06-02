#pragma once
#include <QApplication>
#include <QSettings>
#include "styles.h"
#include "settings.h"

namespace kernel{

    class Application:public QApplication{
    public:
        Application(int &argc, char** argv):
            QApplication(argc,argv){
            setOrganizationName("Oster-Industries");
            setApplicationName("OsterMath");
            __load_settings__();
        }

        ~Application(){
            __save_settings__();
        }

    private:
        static void __save_settings__(){
            ProgramSettings::__save_settings__();
        }

        static void __load_settings__(){
            ProgramSettings::__load_settings__();
        }
    };
}
