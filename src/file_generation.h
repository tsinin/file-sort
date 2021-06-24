//
// Created by tsinin on 6/24/21.
//

#ifndef FILE_SORT_FILE_GENERATION_H
#define FILE_SORT_FILE_GENERATION_H

#include <iostream>
#include <vector>
#include <optional>

namespace file_generation {

char randChar();

std::string randomString(size_t length);

std::vector<std::string> generateTextFile(const std::string& path, int stringNumber, int maxLen,
                                              bool returnVector = false);

}   // namespace file_generation

#endif//FILE_SORT_FILE_GENERATION_H
