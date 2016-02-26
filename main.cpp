#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//
  //  Ui::Find findDialog;
 //   findDialog.setupUi(findDialog);
   // findDialog->show();
    //findDialog->setupUi();


    return a.exec();
}
