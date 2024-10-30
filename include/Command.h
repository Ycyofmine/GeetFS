//
// Created by Ycyofmine on 2024/10/28.
//

#ifndef GEETFS_COMMAND_H
#define GEETFS_COMMAND_H

#include <utility>

#include "GeetFS.h"

class Command {
public:
    virtual void execute(GeetFS& geetFS) = 0;
    virtual ~Command() = default;
};

class WriteCommand : public Command {
public:
    WriteCommand(std::string fileName, int offset, int len, std::string input)
            : fileName(std::move(fileName)), offset(offset), len(len), input(std::move(input)) {}

    void execute(GeetFS& geetFS) override;

private:
    std::string fileName;
    int offset;
    int len;
    std::string input;
};

class ReadCommand : public Command {
public:
    explicit ReadCommand(std::string fileName, int offset, int len) :
        fileName(std::move(fileName)), offset(offset), len(len) {}

    void execute(GeetFS &geetFS) override;

private:
    std::string fileName;
    int offset;
    int len;
};

class lsCommand : public Command {
public:
    void execute(GeetFS &geetFS) override;

private:
    int cnt = 0;
    std::set<std::string> st;
    std::map<std::string, int> ok;
    std::map<std::string, int> time;
};

class unlinkCommand : public Command {
public:
    explicit unlinkCommand(std::string fileName) : fileName(std::move(fileName)) {}

    void execute(GeetFS &geetFS) override;

private:
    std::string fileName;
};

class checkoutCommand : public Command {
public:
    explicit checkoutCommand(std::string cmtName) : cmtName(std::move(cmtName)) {}


    void execute(GeetFS &geetFS) override;

private:
    std::string cmtName;
};

class CommitCommand : public Command {
public:
    explicit CommitCommand(std::string cmtName) : cmtName(std::move(cmtName)) {}

    void execute(GeetFS &geetFS) override;

private:
    std::string cmtName;
};

class mergeCommand : public Command {
public:
    mergeCommand(std::string mergee, std::string cmtName) : mergee(std::move(mergee)), cmtName(std::move(cmtName)) {}

    void execute(GeetFS &geetFS) override;

private:
    std::string mergee;
    std::string cmtName;
};

#endif //GEETFS_COMMAND_H
