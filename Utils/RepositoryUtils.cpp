//
// Created by ilciab on 11/26/25.
//

#include "RepositoryUtils.h"



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

std::string timePointToString(const std::chrono::system_clock::time_point &tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
};