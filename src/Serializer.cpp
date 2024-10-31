//
// Created by Ycyofmine on 2024/10/30.
//

#include "Serializer.h"

// 构造函数
Serializer::Serializer(const std::string &rootAddress) : rootAddress(rootAddress) {
    std::filesystem::create_directories(rootAddress + "/head");
    std::filesystem::create_directories(rootAddress + "/uncommited");
    std::filesystem::create_directories(rootAddress + "/id");
}

void Serializer::saveCommit(const Commit &commit, const std::string &directory) {
    std::filesystem::create_directory(directory);

    std::ofstream nameFile(directory + "/cmtName.txt");
    nameFile << commit.cmtName;
    nameFile.close();

    for (const auto &file : commit.files) {
        std::ofstream fileStream(directory + "/" + file.name + ".txt");
        fileStream << file.name << "\n" << file.content << "\n" << file.time;
        fileStream.close();
    }

    for (const auto &subCommit : commit.facmt) {
        saveCommit(subCommit, directory + "/" + subCommit.cmtName);
    }
}

Commit Serializer::loadCommit(const std::string &directory) {
    Commit ret;

    //cmtName
    std::ifstream nameFile(directory + "/cmtName.txt");
    std::getline(nameFile, ret.cmtName);
    nameFile.close();

    //files
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::ifstream fileStream(entry.path());

            if (!fileStream) continue;

            File file;
            std::getline(fileStream, file.name);
            std::getline(fileStream, file.content);
            fileStream >> file.time;
            ret.files.insert(file);
        }
    }

    //facmt
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (!entry.is_directory())
            continue;
        Commit subCommit = loadCommit(entry.path().string());
        ret.facmt.insert(subCommit);
    }


    return ret;
}

void Serializer::saveGeetFS(const Commit &head, const Commit &uncommitted, const std::map<std::string, Commit> &id) {
    //清空之前内容
    std::filesystem::remove_all(rootAddress + "/head");
    std::filesystem::remove_all(rootAddress + "/uncommited");
    std::filesystem::remove_all(rootAddress + "/id");

    std::filesystem::create_directories(rootAddress + "/head");
    std::filesystem::create_directories(rootAddress + "/uncommited");
    std::filesystem::create_directories(rootAddress + "/id");

    saveCommit(head, rootAddress + "/head");
    saveCommit(uncommitted, rootAddress + "/uncommited");

    for (const auto &[cmtName, cmt] : id) {
        saveCommit(cmt, rootAddress + "/id/" + cmtName);
    }
}

void Serializer::loadGeetFS(Commit &head, Commit &uncommitted, std::map<std::string, Commit> &id) {
    head = loadCommit(rootAddress + "/head");
    uncommitted = loadCommit(rootAddress + "/uncommited");

    for (const auto &entry : std::filesystem::directory_iterator(rootAddress + "/id")) {
        if (!entry.is_directory())
            continue;

        std::string cmtName = entry.path().filename().string();
        id[cmtName] = loadCommit(entry.path().string());
    }
}