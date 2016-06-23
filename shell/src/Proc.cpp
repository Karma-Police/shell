//
// Created by michael on 21.06.16.
//

#include "Proc.h"
#include "Shell.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <fnmatch.h>
#include <signal.h>

using namespace std;
using namespace shell;

const string Proc::PROC_DIR = "/proc";

void Proc::killProcess(pid_t pid) {
    if (kill(pid, SIGKILL) == -1) {
        cout << FAILED_TO_KILL << endl;
    }
}

void Proc::listAllProcesses() {
    dirent **procDirs;
    int procDirsCnt = scandir(PROC_DIR.c_str(), &procDirs, procDirFilter, 0);
    if (procDirsCnt < 0) {
        cout << FAILED_TO_PROC << endl;
        return;
    }
    for (int i = 0; i < procDirsCnt; i++) {
        printProcInfo(procDirs[i]);
        delete (procDirs[i]);
    }
    delete (procDirs);
}

int Proc::procDirFilter(const dirent *dir) {
    return !fnmatch("[1-9]*", dir->d_name, 0);
}

void Proc::printProcInfo(const dirent *dir) {
    string statPath = string(PROC_DIR) + "/" + string(dir->d_name) + "/stat";
    ifstream statFile(statPath);
    string description = "";
    statFile >> description >> description;
    if (description.length() < 2) {
        cout << FAILED_TO_STAT << endl;
        return;
    }
    description = description.substr(1, description.length() - 2); //remove brackets
    cout << setw(10) << string(dir->d_name) << "  " << description << endl;
}
