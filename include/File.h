//
// Created by Ycyofmine on 2024/10/28.
//

#ifndef GEETFS_FILE_H
#define GEETFS_FILE_H

#include <string>
#include <iostream>
#include <utility>

class File {
public:
    std::string name;
    std::string content;
    int time;

    File(std::string name, std::string content, int time);
    File();

    bool operator<(const File &other) const;

    void write(int offset, int len, std::string input);
    void display(int offset, int len);
};

#endif //GEETFS_FILE_H
