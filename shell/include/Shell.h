//
// Created by michael on 19.06.16.
//

#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H

#include <string>
#include <vector>

namespace shell {
    static const std::string GREETING = "Welcome to pShell. P means painful. I know it hurts...";
    static const std::string PREFIX = ">> ";
    static const std::string UNKNOWN_COMMAND = "Error! Unknown command.";
    static const std::string EMPTY_STR = "Got an empty query : ";
    static const std::string NEXT_QUERY = "Got query : ";
    static const std::string EXIT_WITH_ARGUMENTS = "Error! Exit expects no arguments!";
    static const std::string PS_WITH_ARGUMENTS = "Error! PS expects no arguments!";
    static const std::string KILL_DESCRIPTION = "Kill expects one argument - process id that should be killed";
    static const std::string FAILED_TO_RUN = "Error! Unable to fork!";
    static const std::string FAILED_TO_PROC = "Error! Unable to get processes!";
    static const std::string FAILED_TO_STAT = "Failed to read process status!";
    static const std::string FAILED_TO_KILL = "Failed to kill process!";
    static const std::string TOO_MANY_ARGS = "Too many arguments!";
    static const std::string GOT_STRING_TO_INT_EXCEPTION = "Too many arguments!";


    enum Command_type {
        T_EMPTY, T_UNKNOWN, T_EXIT, T_PS, T_KILL
    };

    class Command {
    public:
        const std::string command;
        const Command_type type;
        const std::vector<std::string> *const keys;

        Command(std::string command, Command_type type, std::vector<std::string> *keys) : command(command), type(type),
                                                                                          keys(keys) { }

        ~Command() {
            delete (keys);
        }

    private:
        Command(const Command &) = delete;
    };
}


class Shell {
public:
    Shell();

    int run();

    void printLog();

private:
    std::vector<std::string> logs;
    bool isRunning = false;

    void log(const std::string &message);

    void processCommand(std::string message);

    void processExit(const shell::Command *command);

    void processEmpty(const shell::Command *command);

    int runProgram(const shell::Command *command);

    void processPS(const shell::Command *command);

    void processKill(const shell::Command *command);
};


#endif //SHELL_SHELL_H
