#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keilpackxmlcreate.h"


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


void MainWindow::on_CreateButton_clicked()
{
    pdsc.setKeilPackParams("xiaopb-name","soft","1.0.2","xiaopb");
    pdsc.KeilCreatePdscFile();

}
