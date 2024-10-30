//
// Created by Ycyofmine on 2024/10/28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "../include/mainwindow.h"
#include "ui_MainWindow.h"

#include <QPushButton>
#include <QIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <sstream>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), commandInput(new QLineEdit(this)),
          submitButton(new QPushButton("Execute", this)), outputDisplay(new QTextEdit(this)) {

    // 设置布局
    auto *mainLayout = new QVBoxLayout;
    auto *inputLayout = new QHBoxLayout;

    // 添加输入框和按钮
    inputLayout->addWidget(commandInput);
    inputLayout->addWidget(submitButton);
    mainLayout->addLayout(inputLayout);

    // 添加输出显示框
    mainLayout->addWidget(outputDisplay);
    outputDisplay->setReadOnly(true);

    auto *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // 连接按钮点击事件到槽函数
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::onCommandSubmit);
}

MainWindow::~MainWindow() = default;

void MainWindow::onCommandSubmit() {
    QString command = commandInput->text();

    // 将 QString 转为 std::string
    std::string cmd = command.toStdString();

    // 将命令解析为命令名称和参数列表
    std::istringstream iss(cmd);
    std::string cmdName;
    iss >> cmdName;

    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }

    // 调用 GeetFS 的 solve 方法
//    try {
//        geetFS.solve(cmdName, args);
//        outputDisplay->append("Command executed: " + command);
//    } catch (const std::exception &e) {
//        outputDisplay->append("Error: " + QString::fromStdString(e.what()));
//    }

    commandInput->clear();
}