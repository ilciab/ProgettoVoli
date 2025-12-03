//
// Created by ilciab on 11/26/25.
//

#include "RepositoryUtils.h"
#include <iomanip>



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
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M");
    return ss.str();
};

int stringToPositiveInteger(const std::string &string) {
    try {
        int result = std::stoi(string);

        if (result < 0)
            return -1;

        return result;
    } catch (...) { return -1; }
}


std::optional<std::chrono::system_clock::time_point> stringToTimePoint(const std::string &string) {
    std::chrono::system_clock::time_point tp;
    std::istringstream ss(string);

    if (!(ss >> std::chrono::parse("%F %R", tp))) {
        return std::nullopt;
    }

    return tp;
}

