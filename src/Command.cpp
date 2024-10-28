//
// Created by Ycyofmine on 2024/10/28.
//

#include <functional>
#include "Command.h"
#include "Commit.h"


void WriteCommand::execute(GeetFS &geetFS) {
    std::string _fileName = fileName + "-";
    if (geetFS.searchUncommitted(fileName)) {
        File now_file = *geetFS.findUncommittedFile(fileName);
        now_file.write(offset, len, input);
    }
    else {
        if (geetFS.searchUncommitted(_fileName)) {
            geetFS.deleteUncommitted(_fileName);
            geetFS.insertUncommitted(fileName, "", offset, len, input);
        }
        else {
            int ok = 0;
            Commit res;
            int pre_time = -1;

            geetFS.serCommited([&](const Commit &now_commit) {
                auto now_file = now_commit.files.find(File{fileName, "", 0});
                auto now_file_ = now_commit.files.find(File{_fileName, "", 0});

                if (now_file != now_commit.files.end() && now_file->time >= pre_time) {
                    pre_time = now_file->time;
                    ok = 2;
                    res = now_commit;
                }
                if (now_file_ != now_commit.files.end() && now_file_->time >= pre_time) {
                    pre_time = now_file_->time;
                    ok = 1;
                    res = now_commit;
                }
            });

            if (!ok) {
                geetFS.insertUncommitted(fileName, "", offset, len, input);
            }
            else if (ok == 1) {
                geetFS.insertUncommitted(fileName, "", offset, len, input);
            }
            else {
                File now_file = *res.files.find(File{fileName, std::string(""), 0});
                geetFS.insertUncommitted(fileName, now_file.content, offset, len, input);
            }
        }
    }
}

void ReadCommand::execute(GeetFS &geetFS) {
    std::string _fileName = fileName + "-";
    if (geetFS.searchUncommitted(fileName)) {
        File now_file = *geetFS.findUncommittedFile(fileName);
        now_file.display(offset, len); 
    } else {
            if (geetFS.searchUncommitted(_fileName)) {
                while (len--)
                    std::cout << ".";
                std::cout << "\n";
            }
            else {
                int ok = 0;
                Commit res;
                int pre_time = 0;

                geetFS.serCommited([&](const Commit &now_commit) {
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
            });

            if (!ok) {
                while (len--)
                    std::cout << ".";
                std::cout << "\n";
            }
            else if (ok == 1) {
                while (len--)
                    std::cout << ".";
                std::cout << "\n";
            }
            else {
                File now_file = *res.files.find(File{fileName, std::string(""), 0});
                now_file.display(offset, len);
            }
        }
    }
}

void lsCommand::execute(GeetFS &geetFS) {
    
}

void unlinkCommand::execute(GeetFS &geetFS) {

}

void checkoutCommand::execute(GeetFS &geetFS) {

}

void commitCommand::execute(GeetFS &geetFS) {

}

void mergeCommand::execute(GeetFS &geetFS) {

}