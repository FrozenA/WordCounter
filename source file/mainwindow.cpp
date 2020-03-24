#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "WordCounter.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString int_to_Qstring(int a){
    QString str = "";
    if(a==0)
        str += '0';
    while(a){
        str += a%10+'0';
        a/=10;
    }
    reverse(str.begin(),str.end());
    return str;
}

void MainWindow::on_pushButton_clicked()
{
    QString FilePath = QFileDialog::getOpenFileName(this);
    WC wc;
    if(wc.open(FilePath.toStdString())){
        wc.count();
        QString str="";
        ((str += " 字符 数量 ： ")+= int_to_Qstring(wc.num.ch))+= "\n";
        ((str += " 单词 数量 ： ")+= int_to_Qstring(wc.num.word))+= "\n";
        ((str += " 行数 ：")+= int_to_Qstring(wc.num.line))+= "\n";
        ((str += " 代码行 ：")+= int_to_Qstring(wc.num.codeline))+= "\n";
        ((str += " 注释行 ：")+= int_to_Qstring(wc.num.comment))+= "\n";
        (str += " 空白行 ：")+= int_to_Qstring(wc.num.spaceline);
        QMessageBox::information(this,"Word Counter",str);
    }
}
