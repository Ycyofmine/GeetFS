//
// Created by Ycyofmine on 2024/10/28.
//

#include "GeetFS.h"

bool GeetFS::searchUncommitted(const std::string &fileName) {
    return uncommited.search(fileName);
}

void GeetFS::deleteUncommitted(const std::string &fileName) {
    uncommited.del(fileName);
}

void GeetFS::insertUncommitted(const std::string &fileName, const std::string &content, int offset, int len, const std::string &input) {
    uncommited.ins(fileName, content, offset, len, input);
}

const File* GeetFS::findUncommittedFile(const std::string &fileName) {
    return searchFileUncommitted(fileName, "", 0);
}

const File* GeetFS::searchFileUncommitted(const std::string& fileName, const std::string& content, int time) {
    auto it = uncommited.files.find(File{fileName, std::string(""), time});

    return it != uncommited.files.end() ? &(*it) : nullptr;
}

void GeetFS::serCommited(const std::function<void(const Commit &)> &action) {
    action(head);

    for (const auto &childCommit : head.facmt) {
        serCommited(action);
    }
}

void GeetFS::solve() {

}