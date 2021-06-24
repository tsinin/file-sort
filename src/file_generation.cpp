//
// Created by tsinin on 6/24/21.
//
#include "file_generation.h"

#include <fstream>

namespace file_generation {

const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
const size_t max_index = (sizeof(charset) - 1);

// generates random char from charset
char randChar() {
    return charset[rand() % max_index];
}

// generates random string of given length from charset
std::string randomString(size_t length) {
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randChar);
    return str;
}

// generates file with given string number, max string length.
// Also can return a vector of strings written, optional.
std::vector<std::string> generateTextFile(const std::string& path, int stringNumber, int maxLen,
                                          bool returnVector) {
    std::vector<std::string> ret;

    // create file (delete if exists)
    std::ofstream file(path, std::ios_base::out | std::ios_base::trunc);
    if (!file.is_open()) {
        std::cerr << "file_generation::generateTextFile: error while opening file\n";
        return ret;
    }

    std::string newString;
    for (int i = 0; i < stringNumber; ++i) {
//          if (i % 1000000 == 0) {
//              std::cout << i << '\n';
//          }
        newString = randomString(rand() % maxLen + 1);
        file << newString << '\n';
        if (returnVector) {
            ret.emplace_back(newString);
        }
    }
    return ret;
}

}   // namespace file_generation