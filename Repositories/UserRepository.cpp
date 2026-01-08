
#include "UserRepository.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../Domain/Admin.h"
#include "../Factories/UserFactory.h"
#include "../Services/AuthService.h"
#include "../Utils/RepositoryUtils.h"


void UserRepository::createDefaultAdmin(const unsigned int largestId) {
    AdminFactory adminFactory;
    std::string defaultAdminName = "Admin";
    std::string defaultAdminEmail = "admin";
    std::string defaultAdminPassword = "admin";
    std::string hashedPassword = AuthService::hashPassword(defaultAdminPassword);
    users.push_back(adminFactory.createUser(largestId+1, defaultAdminName, defaultAdminEmail, hashedPassword));
}


void UserRepository::load() {
    std::fstream customerIn = openFile(customerPath, std::ios::in);
    std::fstream adminIn = openFile(adminPath, std::ios::in);

    unsigned int largestId = 0;
    std::string line;
    std::string idStr, name, email, hashedPassword;
    while (std::getline(customerIn, line)) {
        std::stringstream ss(line);
        std::getline(ss, idStr, ';');
        std::getline(ss, name, ';');
        std::getline(ss, email, ';');
        std::getline(ss, hashedPassword, ';');
        unsigned int id;

        try {
            id = std::stoul(idStr);
        } catch (std::exception&) {
            continue;
        }
        users.push_back(customerFactory.createUser(id,name,email,hashedPassword));
        largestId = std::max(largestId, id);
    }


    bool adminLoaded = false;
    if (std::getline(adminIn, line) && !line.empty()) {
        std::stringstream ss(line);
        std::getline(ss, idStr, ';');
        std::getline(ss, name, ';');
        std::getline(ss, email, ';');
        std::getline(ss, hashedPassword, ';');

        if (!idStr.empty() && !name.empty() && !email.empty() && !hashedPassword.empty()) {
            try {
                unsigned int id = std::stoul(idStr);
                users.push_back(adminFactory.createUser(id, name, email, hashedPassword));
                largestId = std::max(largestId, id);
                adminLoaded = true;
            } catch (...) {}
        }
    }

    customerIn.close();
    adminIn.close();

    if (!adminLoaded) {
        std::filesystem::remove(adminPath);
        createDefaultAdmin(largestId);
        largestId++;
    }

    idGen.setStartingId(largestId);

}

void UserRepository::write() {
    std::fstream customerOut = openFile(customerPath,std::ios::out);
    std::fstream adminOut = openFile(adminPath, std::ios::out);

    if (!customerOut.is_open()) {
        std::cerr << "Errore nell'apertura file clienti\n";
        return;
    }

    for (const auto& user : users) {
        if (user->getRole() == UserRole::Customer)
        {
            customerOut << user -> getId() << ';'
                << user -> getName() << ';'
                << user -> getEmail() << ';'
                << user -> getHashedPassword() << ';'
                << '\n';
        }
        else if (user -> getRole() == UserRole::Admin) {
            adminOut << user -> getId() << ';'
                << user -> getName() << ';'
                << user -> getEmail() << ';'
                << user -> getHashedPassword() << ';'
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

unsigned int UserRepository::createCustomer(const std::string & name, const std::string & email, const std::string & hashedPassword) {
    unsigned int id = idGen.getNextId();
    users.emplace_back(std::make_unique<Customer>(id,name,email,hashedPassword));
    return id;
}

unsigned int UserRepository::createAdmin(const std::string & name, const std::string & email, const std::string & hashedPassword) {
    unsigned int id = idGen.getNextId();
    Admin admin(id, name, email, hashedPassword);
    users.emplace_back(std::make_unique<Admin>(id,name,email,hashedPassword));
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




