//
// Created by Ycyofmine on 2024/10/28.
//

#include "Commit.h"
#include "File.h"

extern int whole_time;

// 重载小于运算符用于比较Commit对象
bool Commit::operator<(const Commit &other) const {
    return cmtName < other.cmtName;
}

// 在files集合中查找指定文件
bool Commit::search(const std::string &fileName) const {
    return files.find(File{fileName, "", 0}) != files.end();
}

// 删除files集合中指定文件
bool Commit::del(const std::string &fileName) {
    auto it = files.find(File{fileName, "", 0});
    if (it != files.end()) {
        files.erase(it);
        return true;
    }
    return false;
}

// 向files集合中插入文件并写入内容
void Commit::ins(const std::string &fileName, std::string content, int offset, int len, const std::string &input) {
    File file(fileName, std::move(content), whole_time);
    file.write(offset, len, input);
    files.emplace(std::move(file));
}

// 检查files集合是否为空
bool Commit::isEmpty() const {
    return files.empty();
}

// 清空Commit对象的数据
void Commit::clear() {
    cmtName.clear();
    files.clear();
    facmt.clear();
}