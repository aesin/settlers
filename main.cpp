#include <QtGui>
#include "ui.h"
#include <iostream>
#include <ctime>

int main(int argc, char** argv)
{
    QApplication q_app(argc, argv);
    settlers::Menu main_menu;
    std::srand(std::time(0));
    
    main_menu.Init(&q_app);
    QObject::connect(&main_menu, SIGNAL(Quit()), &q_app, SLOT(quit()));
    q_app.exec();
    
    return 0;
}
