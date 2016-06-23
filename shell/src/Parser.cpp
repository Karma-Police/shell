//
// Created by michael on 21.06.16.
//

#include "Parser.h"
#include "Shell.h"


using namespace shell;

Command * Parser::parse(std::string text) {
    text = Parser::strip(text);
    if (Parser::isEmpty(text)) {
        return new Command("", T_EMPTY, nullptr);
    }

    std::string command = readNextWord(text);
    std::vector<std::string> *keys = new std::vector<std::string>();
    keys->push_back(command);
    while (text != "") {
        keys->push_back(Parser::readNextWord(text));
    }

    if (command == "exit") {
        return new Command(command, T_EXIT, keys);
    } else if (command == "ps") {
        return new Command(command, T_PS, keys);
    } else if (command == "kill") {
        return new Command(command, T_KILL, keys);
    } else {
        return new Command(command, T_UNKNOWN, keys);
    }
}

bool Parser::isEmpty(const std::string &text) {
    for (size_t i = 0; i < text.length(); i++) {
        if (!isspace(text[i])) {
            return false;
        };
    }
    return true;
}

std::string Parser::readNextWord(std::string &text) {
    text = Parser::strip(text);
    std::string result = "";
    size_t pos = 0;
    for (pos = 0; pos < text.length(); pos++) {
        if (!isspace(text[pos])) {
            result += text[pos];
        } else {
            ++pos;
            break;
        }
    }
    text = text.substr(pos);
    text = Parser::strip(text);
    return result;
}

std::string Parser::strip(const std::string &text) {
    for (unsigned i = 0; i < text.length(); i++) {
        if (!isspace(text[i])) {
            return text.substr(i);
        }
    }
    return "";
}

