//
// Created by ciabu on 25/09/2025.
//

#include "AuthService.h"

#include <iostream>


AuthService::AuthService(UserRepository& repo) : repo(repo) {}


std::optional<unsigned int> AuthService::login(const std::string& email, const std::string& password) {
    const User* user = repo.getUserbyEmail(email);
    std::string hashedPassword = hashPassword(password);

    if (user == nullptr) {
        return std::nullopt;
    }

    if (user->gethashedPassword() == hashedPassword)
        return user->getId();

    return std::nullopt;

    //todo differenziare MailNotFound da WrongPassword
}

std::optional<unsigned int> AuthService::signIn(const std::string & name , const std::string & email, const std::string & password) {
    if (repo.getUserbyEmail(email) != nullptr) //esiste già un utente con quella mail
        return std::nullopt;
    return repo.createUser(name, email,hashPassword(password));;
}


std::string AuthService::hashPassword(const std::string& password) {
    uint64_t h = 5381;
    for (unsigned char c : password)
        h = (h*33) + c;
    return std::to_string(h);
}

void AuthService::close() {
    std::cout<<"Suca";
    repo.save();
}
