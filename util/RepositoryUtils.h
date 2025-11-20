//
// Created by ilciab on 11/20/25.
//

#ifndef PROGETTOVOLI_REPOSITORYUTILS_H
#define PROGETTOVOLI_REPOSITORYUTILS_H
#include <memory>
#include <vector>

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

std::fstream openFile(const std::string& path, const std::ios::openmode& mode) {
    std::fstream file(path, mode);
    if (!file) {
        std::ofstream create(path);
        create.close();
        file.open(path, mode);
    }
    return file;
}

void writeBinaryString(std::fstream &file, const std::string &str) {
    size_t length = str.length();
    file.write(reinterpret_cast<const char *>(&length), sizeof(length));
    file.write(str.data(), length);
}

std::string readBinaryString(std::fstream &file) {
    size_t length = 0;

    file.read(reinterpret_cast<char *>(&length), sizeof(length));

    if (file.fail())
        return "";

    std::string str(length, '\0');
    file.read(&str[0], length);

    return str;
}



#endif //PROGETTOVOLI_REPOSITORYUTILS_H