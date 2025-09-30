//
// Created by ciabu on 22/09/2025.
//

#include "User.h"

User::User(const unsigned int id, const std::string& name, const std::string& email, const std::string& hashedPassword) {
    this -> id = id;
    this -> name = name;
    this -> email = email;
    this -> hashedPassword = hashedPassword;
}

const unsigned int& User::getId() const {
    return id;
}

const std::string& User::getName() const {
    return name;
}

const std::string& User::getEmail() const {
    return email;
}

const std::string& User::gethashedPassword() const {
    return hashedPassword;
}

