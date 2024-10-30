//
// Created by Ycyofmine on 2024/10/28.
//

#ifndef UNTITLED_MAINWINDOW_H
#define UNTITLED_MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

#include "GeetFS.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void onCommandSubmit();

private:
    QLineEdit *commandInput;
    QPushButton *submitButton;
    QTextEdit *outputDisplay;
    GeetFS &geetFS = GeetFS::getInstance();  // 假设 geetFS 是一个已经初始化的对象
};


#endif //UNTITLED_MAINWINDOW_H
