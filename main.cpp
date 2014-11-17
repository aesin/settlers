#include <QtGui>
#include "ui.h"
#include <iostream>

int main(int argc, char** argv)
{
    QApplication q_app(argc, argv);
    settlers::Menu main_menu;
    
    main_menu.Init(&q_app);
    QObject::connect(&main_menu, SIGNAL(Quit()), &q_app, SLOT(quit()));
    q_app.exec();
    
    return 0;
}
