//
// Created by Ycyofmine on 2024/10/30.
//

#ifndef GEETFS_SERIALIZER_H
#define GEETFS_SERIALIZER_H
#include <fstream>
#include <filesystem>

#include "GeetFS.h"

class Serializer {
public:
    explicit Serializer(const std::string &rootAddress);

    void saveCommit(const Commit &commit, const std::string &directory);
    Commit loadCommit(const std::string &directory);

    void saveGeetFS(const Commit &head, const Commit &uncommitted, const std::map<std::string, Commit> &id);
    void loadGeetFS(Commit &head, Commit &uncommitted, std::map<std::string, Commit> &id);

private:
    std::string rootAddress;
};

#endif //GEETFS_SERIALIZER_H
