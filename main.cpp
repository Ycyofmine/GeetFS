#include <QApplication>

#include "include/mainwindow.h"
#include "GeetFS.h"
#include "Command.h"

constexpr int N = 2e5 + 5;
int whole_time = 0;

Commit cmt[N];


int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//
//    MainWindow w;
//    w.show();
//
//    return QApplication::exec();

    GeetFS& geetFS = GeetFS::getInstance();


    WriteCommand("file1", 3, 2, "ab").execute(geetFS);
    CommitCommand("cmt1").execute(geetFS);
    WriteCommand("file2", 2, 4, "cdef").execute(geetFS);
    ReadCommand("file1", 0, 10).execute(geetFS);
    lsCommand().execute(geetFS);
    unlinkCommand("file1").execute(geetFS);
    CommitCommand("cmt2").execute(geetFS);
    lsCommand().execute(geetFS);
    checkoutCommand("cmt1").execute(geetFS);
    ReadCommand("file1", 0, 10).execute(geetFS);
    std::cerr << "iwashere" << std::endl;
    WriteCommand("file1", 6, 2, "gh").execute(geetFS);
    WriteCommand("file3", 2, 3, "ijk").execute(geetFS);
    CommitCommand("cmt3").execute(geetFS);
    lsCommand().execute(geetFS);
    checkoutCommand("cmt2").execute(geetFS);
    lsCommand().execute(geetFS);
    mergeCommand("cmt3", "cmt4").execute(geetFS);
    lsCommand().execute(geetFS);
    ReadCommand("file3", 0, 10).execute(geetFS);
    checkoutCommand("cmt3").execute(geetFS);
    WriteCommand("file3", 5, 3, "lmn").execute(geetFS);
    ReadCommand("file3", 0, 10).execute(geetFS);

//    geetFS.loadFromTxt(std::string(R"(D:\Games\GeetFS\resources\data.txt)"));
    geetFS.saveToTxt(std::string(R"(D:\Games\GeetFS\resources\data.txt)"));

    geetFS.solve();
}
