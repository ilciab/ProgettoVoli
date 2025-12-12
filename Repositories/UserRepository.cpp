//
// Created by ciabu on 23/09/2025.
//

#include "UserRepository.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../Domain/Admin.h"
#include "../Utils/RepositoryUtils.h"


void UserRepository::load() {
    std::fstream customerIn = openFile(customerPath, std::ios::in);
    std::fstream adminIn = openFile(adminPath, std::ios::in);

    unsigned int largestId = 0;
    std::string line;
    std::string idStr, name, email, hashedPassword, customerLevelString;
    CustomerLevel customerLevel;
    AdminLevel adminLevel;
    while (std::getline(customerIn, line)) {
        std::stringstream ss(line);
        std::getline(ss, idStr, ';');
        std::getline(ss, name, ';');
        std::getline(ss, email, ';');
        std::getline(ss, hashedPassword, ';');
        std::getline(ss, customerLevelString, ';');
        //todo fix se non c'è un id
        unsigned int id = std::stoul(idStr);
        customerLevel = static_cast<CustomerLevel>(std::stoi(customerLevelString));
        users.emplace_back(std::make_unique<Customer>(id,name,email,hashedPassword,customerLevel));
        largestId = std::max(largestId, id);
    }
    while (std::getline(adminIn, line)) {
        std::stringstream ss(line);
        std::getline(ss, idStr, ';');
        std::getline(ss, name, ';');
        std::getline(ss, email, ';');
        std::getline(ss, hashedPassword, ';');
        std::getline(ss, customerLevelString, ';');
        //todo fix se non c'è un id
        unsigned int id = std::stoul(idStr);
        adminLevel = static_cast<AdminLevel>(std::stoi(customerLevelString));
        users.emplace_back(std::make_unique<Admin>(id,name,email,hashedPassword,adminLevel));
        largestId = std::max(largestId, id);
    }
    idGen.setStartingId(largestId);
    customerIn.close();
    adminIn.close();
}


void UserRepository::write() {
    std::fstream customerOut = openFile(customerPath,std::ios::out);
    std::fstream adminOut = openFile(adminPath, std::ios::out);

    if (!customerOut.is_open()) {
        std::cerr << "Errore nell'apertura file clienti\n";
        return; //todo O gestisci errore diversamente
    }

    for (const auto& user : users) {
        if (user->getRole() == UserRole::Customer)
        {
            customerOut << user -> getId() << ';'
                << user -> getName() << ';'
                << user -> getEmail() << ';'
                << user -> getHashedPassword() << ';'
                << static_cast<int>(std::get<CustomerLevel>(user -> getLevel()))<< ';'
                << '\n';
        }
        else if (user -> getRole() == UserRole::Admin) {
            adminOut << user -> getId() << ';'
                << user -> getName() << ';'
                << user -> getEmail() << ';'
                << user -> getHashedPassword() << ';'
                << static_cast<int>(std::get<AdminLevel>(user -> getLevel()))<< ';'
                << '\n';
        }
    }
    customerOut.close();
    adminOut.close();
}

const User* UserRepository::getByEmail(const std::string& email) const {
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

unsigned int UserRepository::createAdmin(const std::string & name, const std::string & email, const std::string & hashedPassword, const AdminLevel& adminLevel) {
    unsigned int id = idGen.getNextId();
    users.emplace_back(std::make_unique<Admin>(id,name,email,hashedPassword, adminLevel));
    return id;
}

std::vector<const User *> UserRepository::getAll() {
    std::vector<const User *> result;

    for (const auto& user : users) {
        result.push_back(user.get());
    }
    return result;
}

User * UserRepository::getById_internal(const unsigned int id) {
        for (auto& user : users) {
            if (user -> getId() == id)
                return user.get();
        }
        return nullptr;
}

const User* UserRepository::getById(const unsigned int id) const{
    for (const auto& user : users) {
        if (user -> getId() == id)
            return user.get();
    }
    return nullptr;
}

void UserRepository::setUserName(unsigned int userId, const std::string &newName) {
    getById_internal(userId)->setName(newName);
}

void UserRepository::setUserEmail(unsigned int userId, const std::string &newEmail) {
    getById_internal(userId)->setEmail(newEmail);
}

void UserRepository::setUserPassword(unsigned int userId, const std::string &newHashedPassword) {
    User* user = getById_internal(userId);
    user->setHashedPassword(newHashedPassword);
}

void UserRepository::remove(const unsigned int id) {
    removeById(users, id);
}




