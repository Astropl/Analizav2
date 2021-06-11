#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataBase/maindb.h"
#include "KartaPacjenta/carts.h"
#include <iostream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow ();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initWindow()
{
    qWarning ()<< " Jestem w init";
mainDB *mainDb = new mainDB (this);
mainDb->init();
}

void MainWindow::on_pushButton_3_clicked() // Karta Pacjenta
{
Carts *kartaPacjenta = new Carts(this);
kartaPacjenta->show();
}

void MainWindow::on_btnExit_clicked() // Wyjscie
{
destroy ();
}

void MainWindow::on_pushButton_2_clicked() // Pobierz dane pacjenta
{

}


