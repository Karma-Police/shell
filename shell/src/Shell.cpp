//
// Created by michael on 19.06.16.
//

#include "Shell.h"
#include "Parser.h"
#include "Proc.h"
#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
using namespace shell;

Shell::Shell() {
}

int Shell::run() {
    isRunning = true;
    cout << GREETING << endl;
    string nextCommand;
    while (isRunning) {
        cout << PREFIX;
        getline(cin, nextCommand);
        //log(NEXT_QUERY + nextCommand);
        processCommand(nextCommand);
    }
    return 0;
}

void Shell::printLog() {
    for (auto it = logs.begin(); it != logs.end(); it++) {
        cerr << it.base() << endl;
    }
}

void Shell::log(const std::string &message) {
    logs.push_back(message);
}

void Shell::processCommand(std::string text) {
    Command *command = Parser::parse(text);
    switch (command->type) {
        case T_EMPTY :
            processEmpty(command);
            break;
        case T_EXIT :
            processExit(command);
            break;
        case T_PS:
            processPS(command);
            break;
        case T_KILL:
            processKill(command);
            break;
        case T_UNKNOWN:
            runProgram(command);
            break;
        default:
            break;
    }
    delete (command);
}

void Shell::processEmpty(const Command *command) {
    assert(command->type == T_EMPTY);
    log(EMPTY_STR + command->command);
    return;
}

void Shell::processExit(const Command *command) {
    assert(command->type == T_EXIT);
    if (command->keys->size() > 1) {
        log(EXIT_WITH_ARGUMENTS);
        cout << EXIT_WITH_ARGUMENTS << endl;
        return;
    }
    isRunning = false;
}

int Shell::runProgram(const Command *command) {
    assert(command->type == T_UNKNOWN);
    assert(command);
    char **args = new char *[command->keys->size() + 1];
    for (size_t i = 0; i < command->keys->size(); i++) {
        args[i] = const_cast<char *>(command->keys->at(i).c_str());
    }
    args[command->keys->size()] = nullptr;

    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0) { // child process
        if (execvp(command->command.c_str(), args) == -1) { //failed to run
            cout << UNKNOWN_COMMAND << endl;
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        log(FAILED_TO_RUN + " : " + command->command);
        cout << FAILED_TO_RUN << endl;
    } else { // parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    delete[] args;

    return 0;
}

void Shell::processPS(const shell::Command *command) {
    assert(command->type == T_PS);
    if (command->keys->size() > 1) {
        cout << PS_WITH_ARGUMENTS << endl;
        log(PS_WITH_ARGUMENTS);
        return;
    }
    Proc::listAllProcesses();
}

void Shell::processKill(const shell::Command *command) {
    assert(command->type == T_KILL);
    if (command->keys->size() != 2) {
        cout << KILL_DESCRIPTION << endl;
        log(command->command + " : " + TOO_MANY_ARGS);
        return;
    }
    int pid;
    try {
        pid = stoi(command->keys->at(1));
    } catch (...) {
        cout << KILL_DESCRIPTION << endl;
        log(GOT_STRING_TO_INT_EXCEPTION);
        return;
    }
    Proc::killProcess(pid);
}
