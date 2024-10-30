//
// Created by Ycyofmine on 2024/10/28.
//

#ifndef GEETFS_COMMIT_H
#define GEETFS_COMMIT_H

#include <set>
#include <functional>
#include "File.h"

extern int whole_time;

class Commit {
public:
    std::string cmtName;
    std::set<File> files;
    std::set<Commit> facmt;

    bool operator<(const Commit &other) const;
    [[nodiscard]] bool containsFile(const std::string &fileName) const;
    [[nodiscard]] std::set<File>::const_iterator findFile(const std::string &fileName) const;
    bool del(const std::string &fileName);
    void ins(const std::string &fileName, std::string content, int offset, int len, const std::string &input);
    void ins(const std::string &fileName);
    [[nodiscard]] bool isEmpty() const;
    void clear();

};

#endif //GEETFS_COMMIT_H
