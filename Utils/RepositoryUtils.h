//
// Created by ilciab on 11/20/25.
//

#ifndef PROGETTOVOLI_REPOSITORYUTILS_H
#define PROGETTOVOLI_REPOSITORYUTILS_H
#include <chrono>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

template <typename T>

bool removeById(std::vector<std::unique_ptr<T>>& items, unsigned int id) {
    for (int i = 0; i < items.size(); ++i) {
        if (items[i] -> getId() == id) {
            items.erase(items.begin() + i);
            return true;
        }
    }
    return false;
}

std::fstream openFile(const std::string& path, const std::ios::openmode& mode);

void writeBinaryString(std::fstream &file, const std::string &str);

std::string readBinaryString(std::fstream &file);

std::string timePointToString(const std::chrono::system_clock::time_point &tp);

int stringToPositiveInteger(const std::string &string);

std::optional<std::chrono::system_clock::time_point> stringToTimePoint(const std::string &str);



#endif //PROGETTOVOLI_REPOSITORYUTILS_H