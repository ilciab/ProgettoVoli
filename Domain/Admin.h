
#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"


class Admin : public User {

private:
    UserRole userRole = UserRole::Admin;


public:
    UserRole getRole() const override {return userRole;}


    Admin(unsigned int id, const std::string& name, const std::string& email, const std::string& hashedPassword)
        : User(id, name, email, hashedPassword) {}

};


#endif //ADMIN_H
