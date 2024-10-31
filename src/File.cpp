//
// Created by Ycyofmine on 2024/10/28.
//

#include "File.h"



File::File(std::string name, std::string content, int time)
        : name(std::move(name)), content(std::move(content)), time(time) {}

File::File() : name(""), content(""), time(0) {}

bool File::operator<(const File &other) const {
    return name < other.name;
}

void File::write(int offset, int len, std::string input) {
    while ((int)content.size() < offset)
        content += ".";
    int idx = 0;
    while (idx < input.size()) {
        if (offset < content.size())
            content[offset++] = input[idx++];
        else
            content += input[idx++], offset++;
    }
}

void File::display(int offset, int len) {
    for (int j = offset; j <= offset + len - 1; j++) {
        if (j < content.size())
            std::cerr << content[j];
        else
            std::cerr << ".";
    }
    std::cerr << "\n";
}