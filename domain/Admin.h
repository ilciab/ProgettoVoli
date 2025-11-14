//
// Created by ciabu on 30/09/2025.
//

#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"


class Admin : public User {

private:
    AdminLevel level;


public:
    UserRole getRole() const override {return UserRole::Admin;}

    Admin(const unsigned int &id, const std::string& name, const std::string& email, const std::string& hashedPassword)
    : User(id, name, email, hashedPassword) {}
    
};


#endif //ADMIN_H
