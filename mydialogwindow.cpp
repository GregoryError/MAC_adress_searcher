#include "mydialogwindow.h"
#include "ui_mydialogwindow.h"
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QMap>
#include <QMessageBox>
#include <ctype.h>
#include <QtWidgets>


MyDialogWindow::MyDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialogWindow)
{

    ui->setupUi(this);
    ui->Search_button->setEnabled(false);




    //===============================================================





    //===============================================================



    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(SearchEnabled()));
    connect(ui->Search_button, SIGNAL(clicked()), this, SLOT(StartSearch()));
    connect(ui->textBrowser, SIGNAL(textChanged()), this, SLOT(SwapPict()));
    ui->progressBar->setStyleSheet("*::chunk {background-color: #05B8CC; border: 1px solid grey; border-radius: 3px; }");
}

void MyDialogWindow::SwapPict()
{


}

void MyDialogWindow::SearchEnabled()
{
    ui->Search_button->setEnabled(true);
}
void MyDialogWindow::StartSearch()
{
    QFile file(":/table.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           QString problem("Sorry. Can`t open source vendor file table.txt. You should put it into the root folder.");
           QMessageBox msg;
           msg.setText(problem);
           msg.exec();
       }
    QString str, name, key, strmac, line;
    const int pos(20), size(50);
    register int counter(0);
    QMap<QString, QString> dictionary;
    while(!file.atEnd())
            {
                    str = file.readLine();
                    QRegExp re("[0-9A-Fa-f]{6}");
                    if (str.length() > 20 && str[2] != '-' && str.mid(0, 6).contains(re))
                    {                                         // reading from file strings, and writing to dictionary.
                        strmac = str.mid(0, 6);
                        name = str.mid(pos, size);
                        dictionary[strmac] = name;
                        ++counter;
                        ui->progressBar->setValue(counter * 0.0042);
                    }
            }
    for(auto ch : ui->lineEdit->text())
    {
        if(isalnum(ch.toLatin1()))       //  Customize inputting(Latin, Upper, without symbols)
        {
            ch = ch.toUpper();
            line += ch;
        }
    }
   key = line.mid(0, 6);
   ui->textBrowser->append(dictionary[key]);
}

MyDialogWindow::~MyDialogWindow()
{
    delete ui;
}

