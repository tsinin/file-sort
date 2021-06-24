//
// Created by tsinin on 6/24/21.
//

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <map>

namespace file_sorting {

    void sortFile(const std::string& path, const std::string& newPath, uint64_t maxBytesForUse) {
        std::ifstream input(path, std::ios_base::in);
        if (!input.is_open()) {
            std::cerr << "file_sorting::sortFile: error while opening input file.\n";
            return;
        }

        // sort blocks sequentially and write sorted blocks to temporary files

        std::vector<std::string> strings;

        // create temporary directory for sorting files
        std::filesystem::create_directory("../tmp_sorting");

        std::string tmpFileNamePrefix = "../tmp_sorting/.sorting_";

        uint64_t blockSize = 0;
        int blockNum = 0;
        std::string s;
        while (!input.eof()) {
            // adding strings in block until limit exceed or EOF
            while (blockSize < maxBytesForUse && getline(input, s)) {
                strings.emplace_back(s);
                blockSize += s.size() + 12;
            }
            // sort block
            std::sort(strings.begin(), strings.end());
            // write block to temporary file
            std::ofstream tmp_file(tmpFileNamePrefix + std::to_string(blockNum), std::ios_base::out | std::ios_base::trunc);
            if (!tmp_file.is_open()) {
                std::cerr << "file_sorting::sortFile: error while opening temporary file " +
                             tmpFileNamePrefix + std::to_string(blockNum) + " for sorting [1]\n";
                return;
            }
            for (const auto& str : strings) {
                tmp_file << str << '\n';
            }
            tmp_file.close();
            blockNum++;
            blockSize = 0;
            strings.clear();
        }
        input.close();

        // create and open stream for every block (temporary file)
        // if maxBytes is not very small in comparison with input file size,
        // there will be no issues.
        std::vector<std::ifstream> blocks(blockNum);
        for (int i = 0; i < blockNum; ++i) {
            blocks[i].open(tmpFileNamePrefix + std::to_string(i), std::ios_base::in);
            if (!blocks[i].is_open()) {
                std::cerr << "file_sorting::sortFile: error while opening temporary file " +
                             tmpFileNamePrefix + std::to_string(i) + " for sorting [2]\n";
                return;
            }
        }

        // map which stores next line and id for every block
        std::multimap<std::string, int> stringMap;
        for (int i = 0; i < blockNum; ++i) {
            if (getline(blocks[i], s)) {
                stringMap.emplace(s, i);
            }
        }

        // creating output file.
        // can be the same as input
        std::ofstream output(newPath, std::ios_base::out | std::ios_base::trunc);
        if (!output.is_open()) {
            std::cerr << "file_sorting::sortFile: error while opening output file.\n";
            return;
        }

        // merging blocks in output file
        int blockId;
        while (!stringMap.empty()) {
            // get smallest element
            auto it = stringMap.begin();
            s = it->first;
            blockId = it->second;

            // delete it and write to output file
            stringMap.erase(it);
            output << s << '\n';

            // if block is not empty and there is a line,
            // add it to the map.
            if (getline(blocks[blockId], s)) {
                stringMap.emplace(s, blockId);
            } else {
                blocks[blockId].close();
            }
        }

        // close output file and remove directory with temporary files
        output.close();
        std::filesystem::remove_all("../tmp_sorting");
    }

}   // namespace file_sorting