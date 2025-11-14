//
// Created by ciabu on 30/09/2025.
//

#ifndef CLIENT_H
#define CLIENT_H
#include "User.h"


class Customer : public User {

private:
    CustomerLevel level;


public:

    UserRole getRole() const override {return UserRole::Customer;}
    std::variant<CustomerLevel, AdminLevel> getLevel() const override { return level;}

    Customer(const unsigned int &id, const std::string &name, const std::string &email, const std::string &hashedPassword)
        : User(id, name, email, hashedPassword){ level = CustomerLevel::BRONZE;}

    Customer(const unsigned int &id, const std::string &name, const std::string &email, const std::string &hashedPassword, const CustomerLevel& customerLevel)
        : User(id, name, email, hashedPassword){ level = customerLevel;}
};



#endif //CLIENT_H
