//
// Created by ciabu on 23/09/2025.
//

#include "UserRepository.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../domain/Client.h"


UserRepository::UserRepository(const std::string &path) {
    this->path = path;
    UserRepository::load();
}


void UserRepository::add(const User& user) {
}


void UserRepository::load() {
    unsigned int largestId = 0;
    std::ifstream userFile(path);
    if (!userFile) {
        std::ofstream create(path);
        create.close();
        userFile.open(path);
    }
    std::string line;
    std::string idStr, name, email, hashedPassword;
    while (std::getline(userFile, line)) {
        std::stringstream ss(line);
        std::getline(ss, idStr, ';');
        std::getline(ss, name, ';');
        std::getline(ss, email, ';');
        std::getline(ss, hashedPassword, ';');

        unsigned int id = std::stoul(idStr);
        std::cout << email;
        std::cout << hashedPassword;
        users.emplace_back(std::make_unique<User>(id,name,email,hashedPassword));
        largestId = std::max(largestId, id);
    }
    idGen.setStartingId(largestId);
    userFile.close();
}

void UserRepository::save() {
    std::ofstream out(path, std::ios::trunc); // overwrite file
    if (!out) {
        std::ofstream create(path);
        create.close();
        out.open(path);
    }
    for (const auto& user : users) {
        out << user -> getId() << ';'
            << user -> getName() << ';'
            << user -> getEmail() << ';'
            << user -> gethashedPassword().
            << '\n';
    }
}

const User* UserRepository::getUserbyEmail(const std::string& email) {
    for (const auto& user: users) {
        if (user->getEmail()  == email)
            return user.get();
    }
    return nullptr;
}

unsigned int UserRepository::createClient(const std::string & name, const std::string & email, const std::string & hashedPassword) {
    unsigned int id = idGen.getNextId();
    users.emplace_back(std::make_unique<Client>(id,name,email,hashedPassword));
    return id;
}


std::vector<User> UserRepository::getAll() {

}

unsigned int* UserRepository::getById(int id) {

}

void UserRepository::remove(int id) {

}



