#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow wre;

    wre.show();
    return a.exec();
}
