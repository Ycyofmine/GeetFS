#include <QApplication>
#include "include/mainwindow.h"
#include "Commit.h"
#include "File.h"

constexpr int N = 2e5 + 5;
static int whole_time = 0;

Commit cmt[N];


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return QApplication::exec();
}
