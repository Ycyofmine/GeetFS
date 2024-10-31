//
// Created by Ycyofmine on 2024/10/28.
//

#include <functional>
#include "Command.h"
#include "Commit.h"


void WriteCommand::execute(GeetFS &geetFS) {
    std::string _fileName = fileName + "-";
    if (geetFS.fileExists(fileName)) {
        File now_file = *geetFS.findFile(fileName);
        now_file.write(offset, len, input);
    }
    else {
        if (geetFS.fileExists(_fileName)) {
            geetFS.deleteFile(_fileName);
            geetFS.insertFile(fileName, "", offset, len, input);
        }
        else {
            int ok = 0;
            Commit res;
            int pre_time = -1;

            std::function<void(const Commit &)> ser = [&](const Commit &now_commit) {
                auto now_file = now_commit.files.find(File{fileName, std::string(""), 0});
                auto now_file_ = now_commit.files.find(File{_fileName, std::string(""), 0});
                if (now_file != now_commit.files.end()) {
                    if (now_file->time >= pre_time) {
                        pre_time = now_file->time;
                        ok = 2, res = now_commit;
                    }
                }
                if (now_file_ != now_commit.files.end()) {
                    if (now_file_->time >= pre_time) {
                        pre_time = now_file_->time;
                        ok = 1, res = now_commit;
                    }
                }
                for (auto &x : now_commit.facmt) {
                    ser(x);
                }
            };
            ser(geetFS.getHead());

            if (!ok) {
                geetFS.insertFile(fileName, "", offset, len, input);
            }
            else if (ok == 1) {
                geetFS.insertFile(fileName, "", offset, len, input);
            }
            else {
                File now_file = *res.findFile(fileName);
                geetFS.insertFile(fileName, now_file.content, offset, len, input);
            }
        }
    }
}

void ReadCommand::execute(GeetFS &geetFS) {
    std::string _fileName = fileName + "-";
    if (geetFS.fileExists(fileName)) {
        File now_file = *geetFS.findFile(fileName);
        now_file.display(offset, len); 
    } else {
            if (geetFS.fileExists(_fileName)) {
                while (len--)
                    std::cerr << ".";
                std::cerr << "\n";
            }
            else {
                int ok = 0;
                Commit res;
                int pre_time = 0;

                std::function<void(const Commit &)> ser = [&](const Commit &now_commit) {
                    auto now_file = now_commit.files.find(File{fileName, std::string(""), 0});
                    auto now_file_ = now_commit.files.find(File{_fileName, std::string(""), 0});
                    if (now_file != now_commit.files.end()) {
                        if (now_file->time >= pre_time) {
                            pre_time = now_file->time;
                            ok = 2, res = now_commit;
                        }
                    }
                    if (now_file_ != now_commit.files.end()) {
                        if (now_file_->time >= pre_time) {
                            pre_time = now_file_->time;
                            ok = 1, res = now_commit;
                        }
                    }
                    for (auto &x : now_commit.facmt) {
                        ser(x);
                    }
                };
                ser(geetFS.getHead());

            if (!ok) {
                while (len--)
                    std::cerr << ".";
                std::cerr << "\n";
            }
            else if (ok == 1) {
                while (len--)
                    std::cerr << ".";
                std::cerr << "\n";
            }
            else {
                File now_file = *res.findFile(fileName);
                now_file.display(offset, len);
            }
        }
    }
}

void lsCommand::execute(GeetFS &geetFS) {
    int cnt = 0;
    std::set<std::string> st;
    std::map<std::string, int> ok;
    std::map<std::string, int> time;

    std::function<void(const Commit &)> ser = [&](const Commit &now_commit) {
        for (auto x : now_commit.files) {
            if (x.name.back() == '-') {
                x.name.pop_back();
                if (x.time >= time[x.name]) {
                    ok[x.name] = 1;
                    time[x.name] = x.time;
                }
            }
            else {
                if (x.time >= time[x.name]) {
                    ok[x.name] = 2;
                    time[x.name] = x.time;
                }
            }
        }
        for (auto &x : now_commit.facmt) {
            ser(x);
        }
    };
    for (auto x : geetFS.getUncommited().files)
        if (x.name.back() != '-') {
            st.insert(x.name);
        }
        else {
            x.name.pop_back();
            ok[x.name] = 1;
            time[x.name] = INT_MAX;
        }
    ser(geetFS.getHead());
    for (auto [x, y] : ok) {
        if (y == 2)
            st.insert(x);
    }
    if (st.empty())
        std::cerr << st.size() << "\n";
    else
        std::cerr << st.size() << " " << *st.begin() << " " << *st.rbegin() << "\n";
}

void unlinkCommand::execute(GeetFS &geetFS) {
    std::string _fileName = fileName + "-";
    if (geetFS.fileExists(fileName)) {
        geetFS.deleteFile(fileName);
        geetFS.insertFile(_fileName);
    } else {
        int ok = 0;
        int pre_time = -1;

        std::function<void(const Commit &)> ser = [&](const Commit &now_commit) {
            auto now_file = now_commit.files.find(File{fileName, std::string(""), 0});
            auto now_file_ = now_commit.files.find(File{_fileName, std::string(""), 0});
            if (now_file != now_commit.files.end()) {
                if (now_file->time >= pre_time) {
                    pre_time = now_file->time;
                    ok = 2;
                }
            }
            if (now_file_ != now_commit.files.end()) {
                if (now_file_->time >= pre_time) {
                    pre_time = now_file_->time;
                    ok = 1;
                }
            }
            for (const Commit &x : now_commit.facmt) {
                ser(x);
            }
        };
        ser(geetFS.getHead());

        if (ok == 2) {
            geetFS.insertFile(_fileName);
        }
    }
}

void checkoutCommand::execute(GeetFS &geetFS) {
    if (geetFS.id.find(cmtName) == geetFS.id.end() || !geetFS.uncommited.isEmpty())
        return;
    geetFS.head = geetFS.id[cmtName];
}

//偷懒了，要解耦以后再说
void CommitCommand::execute(GeetFS &geetFS) {
    if (geetFS.id.find(cmtName) != geetFS.id.end() || geetFS.uncommited.isEmpty()) {
        return;
    }
    Commit new_commit = geetFS.uncommited;
    new_commit.cmtName = cmtName;
    if (geetFS.head.cmtName != "") {
        new_commit.facmt.insert(geetFS.head);
    }
    geetFS.head = new_commit;
    geetFS.id[cmtName] = geetFS.head;
    geetFS.uncommited.clear();
    whole_time++;
}

void mergeCommand::execute(GeetFS &geetFS) {
    if (!geetFS.uncommited.isEmpty() || mergee == geetFS.head.cmtName || geetFS.id.find(mergee) == geetFS.id.end())
            return;
    Commit pos = geetFS.id[mergee];
    Commit new_commit;
    new_commit.cmtName = cmtName;
    new_commit.facmt.insert(geetFS.head);
    new_commit.facmt.insert(pos);
    geetFS.head = new_commit;
    geetFS.id[cmtName] = geetFS.head;
}