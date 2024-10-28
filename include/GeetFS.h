//
// Created by Ycyofmine on 2024/10/28.
//

#ifndef GEETFS_GEETFS_H
#define GEETFS_GEETFS_H

#include "Commit.h"
#include "File.h"

#include <utility>
#include <map>

class GeetFS {
public:
    void solve();
    const File* searchFileUncommitted(const std::string& fileName, const std::string& content, int time);
    const File* findUncommittedFile(const std::string &fileName);
    bool searchUncommitted(const std::string &fileName);
    void deleteUncommitted(const std::string &fileName);
    void insertUncommitted(const std::string &fileName, const std::string &content, int offset, int len, const std::string &input);
    void serCommited(const std::function<void(const Commit&)>& action);

private:
    Commit head;
    Commit uncommited;
    std::map<std::string, Commit> id;
};

#endif //GEETFS_GEETFS_H
