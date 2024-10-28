//
// Created by Ycyofmine on 2024/10/28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "../include/mainwindow.h"
#include "ui_MainWindow.h"
#include <QPushButton>
#include <QIcon>


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    this->setWindowIcon(QIcon(":/logo/icon3.png"));

    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, [](){
        qDebug() << "QUSHED";
    });
}

MainWindow::~MainWindow() {
    delete ui;
}
