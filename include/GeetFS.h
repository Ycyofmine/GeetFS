//
// Created by Ycyofmine on 2024/10/28.
//

#ifndef GEETFS_GEETFS_H
#define GEETFS_GEETFS_H

#include "Commit.h"
#include "File.h"

#include <utility>
#include <map>
#include <iostream>
#include <fstream>

extern int whole_time;

class GeetFS {
public:
    static GeetFS& getInstance() {
        static GeetFS instance;
        return instance;
    }

    void solve();

    //by name & content & time
    const File* findFile(const std::string& fileName, const std::string& content, int time);
    //by name
    const File* findFile(const std::string &fileName);
    bool fileExists(const std::string &fileName);
    void deleteFile(const std::string &fileName);
    //normal file
    void insertFile(const std::string &fileName, const std::string &content, int offset, int len, const std::string &input);
    //dark file
    void insertFile(const std::string &fileName);
    bool idNotExists(const std::string &cmtName) const;
    bool uncommitedEmpty() const;
    void setHead(const std::string &cmtName);
    void serCommited(const std::function<void(const Commit&)>& action);

    void saveToTxt(const std::string &address) const;
    void loadFromTxt(const std::string &address);

    void saveCommit(std::ofstream &outFile, const Commit &commit) const;
    Commit loadCommit(std::ifstream &inFile);

    [[nodiscard]] const Commit &getUncommited() const;
    [[nodiscard]] const Commit &getHead() const;

    Commit head;
    Commit uncommited;
    std::map<std::string, Commit> id;
private:
    GeetFS() = default;
};

#endif //GEETFS_GEETFS_H
