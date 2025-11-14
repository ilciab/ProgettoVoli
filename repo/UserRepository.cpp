//
// Created by ciabu on 23/09/2025.
//

#include "UserRepository.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../domain/Admin.h"


UserRepository::UserRepository(const std::string &customerPath, const std::string& adminPath) {
    this->customerPath = customerPath;
    this->adminPath = adminPath;
    UserRepository::load();
}


void UserRepository::add(const User& user) {
}


void UserRepository::load() {
    unsigned int largestId = 0;
    std::ifstream userFile(customerPath);
    if (!userFile) {
        std::ofstream create(customerPath);
        create.close();
        userFile.open(customerPath);
    }
    std::string line;
    std::string idStr, name, email, hashedPassword, customerLevelString;
    CustomerLevel customerLevel;
    while (std::getline(userFile, line)) {
        std::stringstream ss(line);
        std::getline(ss, idStr, ';');
        std::getline(ss, name, ';');
        std::getline(ss, email, ';');
        std::getline(ss, hashedPassword, ';');
        std::getline(ss, customerLevelString, ';');
        //todo fix se non c'è un id
        unsigned int id = std::stoul(idStr);
        customerLevel = static_cast<CustomerLevel>(std::stoi(customerLevelString));
        std::cout << email;
        std::cout << hashedPassword;
        users.emplace_back(std::make_unique<Customer>(id,name,email,hashedPassword,customerLevel));
        largestId = std::max(largestId, id);
    }
    idGen.setStartingId(largestId);
    userFile.close();
}


std::ofstream openFile(const std::string& path) {
    std::ofstream out(path, std::ios::trunc);
    if (!out) {
        std::ofstream create(path);
        create.close();
        out.open(path);
    }
    return out;
}

void UserRepository::write() {
    std::ofstream customerOut = openFile(customerPath);
    std::ofstream adminOut = openFile(adminPath);
    for (const auto& user : users) {

        if (user->getRole() == UserRole::Customer) {}
        customerOut << user -> getId() << ';'
            << user -> getName() << ';'
            << user -> getEmail() << ';'
            << user -> getHashedPassword() << ';'
            << static_cast<int>(std::get<CustomerLevel>(user -> getLevel()))<< ';'
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

unsigned int UserRepository::createCustomer(const std::string & name, const std::string & email, const std::string & hashedPassword, const CustomerLevel& customerLevel) {
    unsigned int id = idGen.getNextId();
    users.emplace_back(std::make_unique<Customer>(id,name,email,hashedPassword, customerLevel));
    return id;
}


std::vector<User> UserRepository::getAll() {

}

unsigned int* UserRepository::getById(int id) {

}

void UserRepository::remove(int id) {

}



