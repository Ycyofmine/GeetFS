//
// Created by Ycyofmine on 2024/10/28.
//

#include "GeetFS.h"

//在uncommited中文件是否存在
bool GeetFS::fileExists(const std::string &fileName) const {
    return uncommited.containsFile(fileName);
}

//在uncommited中删除文件
void GeetFS::deleteFile(const std::string &fileName) {
    uncommited.del(fileName);
}

//在uncommited中插入正常文件
void GeetFS::insertFile(const std::string &fileName, const std::string &content, int offset, int len, const std::string &input) {
    uncommited.ins(fileName, content, offset, len, input);
}

//在uncommited中插入暗文件
void GeetFS::insertFile(const std::string &fileName) {
    uncommited.ins(fileName);
}

bool GeetFS::idNotExists(const std::string &cmtName) const
{
    return id.find(cmtName) == id.end();
}

const File* GeetFS::findFile(const std::string &fileName) {
    return findFile(fileName, "", 0);
}

const File* GeetFS::findFile(const std::string& fileName, const std::string& content, int time) {
    auto it = uncommited.files.find(File{fileName, std::string(""), time});

    return it != uncommited.files.end() ? &(*it) : nullptr;
}

bool GeetFS::uncommitedEmpty() const {
    return uncommited.isEmpty();
}

void GeetFS::setHead(const std::string &cmtName) {
    head = id[cmtName];
}

const Commit &GeetFS::getHead() const {
    return head;
}

const Commit &GeetFS::getUncommited() const {
    return uncommited;
}

// //程序要结束时保存文件
// void GeetFS::saveToTxt(const std::string &address) const {
//     std::ofstream outFile(address);

//     if (!outFile.is_open()) {
//         std::cerr << "无法打开文件" << address << std::endl;
//         return;
//     }

//     outFile << "Head Commit:\n";
//     saveCommit(outFile, head);

//     outFile << "\nUncommited Commit:\n";
//     saveCommit(outFile, uncommited);

//     outFile << "\nAll Commits:\n";
//     for (const auto &entry : id) {
//         saveCommit(outFile, entry.second);
//     }

//     outFile.close();
// }

// //head/uncommited/id
// //Commit Name:
// //Files:
// //      name
// //      content
// //      time
// //Sub Commit
// //facmt  Back to line87
// void GeetFS::saveCommit(std::ofstream &outFile, const Commit &commit) const {
//     outFile << "Commit Name: " << commit.cmtName << "\n";

//     for (const auto &file : commit.files) {
//         outFile << "Files:\n";
//         outFile << "Name:" << file.name << "\n";
//         outFile << "Content:" << file.content << "\n";
//         outFile << "Time:" << file.time << "\n";
//     }

//     if (commit.facmt.empty()) {
//         return;
//     }

//     for (const auto &subCommit : commit.facmt) {
//         outFile << "Sub Commits:\n";
//         saveCommit(outFile, subCommit);  // 递归保存子提交
//     }
// }

// //程序开始时载入文件
// void GeetFS::loadFromTxt(const std::string &address) {
//     std::ifstream inFile(address);

//     if (!inFile.is_open()) {
//         std::cerr << "读取失败: " << address << std::endl;
//         return;
//     }

//     std::string line;

//     // 读取 Head Commit
//     std::getline(inFile, line); // "Head Commit:"
//     head = loadCommit(inFile);

//     // 读取 Uncommited Commit
//     std::getline(inFile, line); // "Uncommited Commit:"
//     uncommited = loadCommit(inFile);

//     // 读取 All Commits
//     std::getline(inFile, line); // "All Commits:"
//     std::getline(inFile, line);// first cmt
//     while (!line.empty()) {
//         std::cerr << line << std::endl;
//         if (!(line.substr(0, 12) == "Commit Name:")) {
//             break;
//         }
//         // 提取提交名称并直接传递给 loadCommit
//         std::string commitName = line.substr(13);
//         id[commitName] = loadCommit(inFile, commitName, line);
//     }
// }

// Commit GeetFS::loadCommit(std::ifstream& inFile) {
//     Commit ret;

//     std::string line;
//     std::getline(inFile, line);
//     ret.cmtName = line.substr(13);

//     while (std::getline(inFile, line) && line == "Files:") {
//         File file;
//         std::getline(inFile, line);
//         file.name = line.substr(5);

//         std::getline(inFile, line);
//         file.content = line.substr(8);

//         std::getline(inFile, line);
//         file.time = stoi(line.substr(5));

//         ret.files.insert(file);
//     }

//     if (line == "Sub Commits:") {
//         Commit cmt = loadCommit(inFile);
//         ret.facmt.insert(cmt);
//     }

//     return ret;
// }

// //用于读取数据到id中
// Commit GeetFS::loadCommit(std::ifstream &inFile, const std::string& commitName, std::string &line) {
//     Commit ret;
//     ret.cmtName = commitName;

//     // 读取文件内容
//     while (std::getline(inFile, line) && line == "Files:") {
//         File file;
//         std::getline(inFile, line);
//         file.name = line.substr(5);  // "Name: xxxx"

//         std::getline(inFile, line);
//         file.content = line.substr(8);  // "Content: xxx"

//         std::getline(inFile, line);
//         file.time = std::stoi(line.substr(5));  // "Time: xxx"

//         ret.files.insert(file);
//     }

//     // 读取子提交（Sub Commits）
//     if (line == "Sub Commits:") {
//         Commit cmt = loadCommit(inFile);
//         ret.facmt.insert(cmt);
//     }

//     return ret;
// }

void GeetFS::solve() {
    

}