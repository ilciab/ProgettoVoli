//
// Created by ciabu on 25/09/2025.
//

#include "AuthService.h"

#include "../Domain/UserStruct.h"



UserStruct AuthService::login(const std::string &email, const std::string &password) const {
    UserStruct loginResult{};
    const User *user = repo.getByEmail(email);
    const std::string hashedPassword = hashPassword(password);

    if (user == nullptr) {
        loginResult.responseCode = AuthResponse::WRONG_EMAIL;
        return loginResult;
    }
    if (user->getHashedPassword() != hashedPassword) {
        loginResult.responseCode = AuthResponse::WRONG_PASSWORD;
        return loginResult;
    }

    loginResult.id = user->getId();
    loginResult.role = user->getRole();
    loginResult.responseCode = AuthResponse::OK;
    return loginResult;
}

UserStruct AuthService::signIn(const std::string &name, const std::string &email, const std::string &password) const {
    UserStruct loginResult{};

    //esiste già un utente con quella mail
    if (repo.getByEmail(email) != nullptr) {
        loginResult.responseCode = AuthResponse::WRONG_EMAIL;
        return loginResult;
    }

    loginResult.id = repo.createCustomer(name, email, hashPassword(password));
    loginResult.role = UserRole::Customer;
    loginResult.responseCode = AuthResponse::OK;
    return loginResult;
}


std::string AuthService::hashPassword(const std::string &password) {
    uint64_t h = 5381;
    for (unsigned char c: password)
        h = (h * 33) + c;
    return std::to_string(h);
}

bool AuthService::changeUserPassword(unsigned int userId, const std::string &oldPassword,
    const std::string &newPassword) const {
    std::string oldHashedPassword = hashPassword(oldPassword);
    std::string newHashedPassword = hashPassword(newPassword);
    const User* user = repo.getById(userId);
    if (oldHashedPassword != user->getHashedPassword())
        return false;
    repo.setUserPassword(userId, newHashedPassword);
    return true;
}

void AuthService::close() const {
    repo.write();
}
