//
// Created by michael on 20.06.16.
//

#ifndef SHELL_PARSER_H
#define SHELL_PARSER_H

#include "Shell.h"
#include <string>

namespace shell {
    class Parser {
    public:
        static shell::Command *parse(std::string text);

    private:
        static std::string readNextWord(std::string &text);

        static std::string strip(const std::string &text);

        static bool isEmpty(const std::string &text);

        Parser() = delete;
    };
}

#endif //SHELL_PARSER_H
