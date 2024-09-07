#include <QApplication>
#include "mainWindow.h"
#include <fstream>
#include "virtualkeyboard.h"
#include <QLocale>
int main(int argc, char *argv[])
{
    QLocale locale;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
