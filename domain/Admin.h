//
// Created by ciabu on 30/09/2025.
//

#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"


class Admin : public User {

private:
    AdminLevel level;
    UserRole userRole = UserRole::Admin;


public:
    UserRole getRole() const override {return userRole;}
    std::variant<CustomerLevel, AdminLevel> getLevel() const override { return level;}

    bool setLevel(const std::variant<CustomerLevel, AdminLevel> &level) override {
        if (std::holds_alternative<AdminLevel>(level)) {
            this->level = std::get<AdminLevel>(level);
            return true;
        }
        return false;
    }

    Admin(unsigned int id, const std::string& name, const std::string& email, const std::string& hashedPassword)
        : User(id, name, email, hashedPassword) { level = AdminLevel::BASE;}

    Admin(unsigned int id, const std::string& name, const std::string& email, const std::string& hashedPassword, const AdminLevel& adminLevel)
    : User(id, name, email, hashedPassword) { level = adminLevel;}

};


#endif //ADMIN_H
