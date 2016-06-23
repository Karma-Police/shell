//
// Created by michael on 21.06.16.
//

#ifndef SHELL_PROC_H
#define SHELL_PROC_H

#include <dirent.h>
#include <string>

namespace shell {
    class Proc {
    public:
        static void listAllProcesses();

        static void killProcess(int pid);

    private:
        static const std::string PROC_DIR;

        static int procDirFilter(const dirent *dir);

        static void printProcInfo(const dirent *dir);

        Proc() = delete;
    };
}

#endif //SHELL_PROC_H
