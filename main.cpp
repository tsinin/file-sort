#include <iostream>
#include <fstream>
#include <vector>

#include "src/file_generation.h"
#include "src/file_sorting.h"

int main() {
    auto strings = file_generation::generateTextFile("../file", 1000000, 1000, true);
    std::cout << "generated\n";

    std::sort(strings.begin(), strings.end());
    std::cout << "std::sorted\n";
    file_sorting::sortFile("../file", "../new_file", 1L<<30);
    std::cout << "externally sorted\n";

    std::ifstream input("../new_file", std::ios_base::in);
    if (!input.is_open()) {
        return 1;
    }
    std::vector<std::string> sorted;
    for (std::string s; getline(input, s);) {
        sorted.push_back(s);
    }

    if (sorted.size() != strings.size()) {
        std::cerr << "sizes are not equal\n";
        std::cerr << sorted.size() << " " << strings.size() << '\n';
        return 1;
    }
    for (int i = 0; i < sorted.size(); ++i) {
        if (sorted[i] != strings[i]) {
            std::cerr << i << " " << sorted[i] << " " << strings[i] << '\n';
            return 1;
        }
    }

    return 0;
}
