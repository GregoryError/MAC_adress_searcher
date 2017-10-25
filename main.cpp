#include "ui_mydialogwindow.h"
#include <QApplication>
#include "mydialogwindow.h"
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyDialogWindow *wnd = new MyDialogWindow;
   // QWidget *wnd = new QWidget;
    //wnd->setAutoFillBackground(true);
    wnd->setWindowTitle("OfflineMacFinder");

    wnd->show();

    return a.exec();
}
