//
// Created by ciabu on 25/09/2025.
//

#include "AuthService.h"

#include "../Domain/UserStruct.h"



std::optional<UserStruct> AuthService::login(const std::string &email, const std::string &password) {
    UserStruct loginResult;
    const User *user = repo.getByEmail(email);
    const std::string hashedPassword = hashPassword(password);

    if (user == nullptr) {
        return std::nullopt;
    }
    if (user->getHashedPassword() != hashedPassword)
        return std::nullopt;

    loginResult.id = user->getId();
    loginResult.role = user->getRole();

    return loginResult;
    //todo differenziare MailNotFound da WrongPassword
}

std::optional<UserStruct> AuthService::signIn(const std::string &name, const std::string &email, const std::string &password) {
    UserStruct loginResult;
    if (repo.getByEmail(email) != nullptr) //esiste già un utente con quella mail
        return std::nullopt;
    loginResult.id = repo.createCustomer(name, email, hashPassword(password), CustomerLevel::BRONZE);
    loginResult.role = UserRole::Customer;

    return loginResult;
}


std::string AuthService::hashPassword(const std::string &password) {
    uint64_t h = 5381;
    for (unsigned char c: password)
        h = (h * 33) + c;
    return std::to_string(h);
}

void AuthService::close() {
    repo.write();
}
