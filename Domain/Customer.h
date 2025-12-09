//
// Created by ciabu on 30/09/2025.
//

#ifndef CLIENT_H
#define CLIENT_H
#include "User.h"



class Customer : public User {

private:
    CustomerLevel level;
    UserRole userRole = UserRole::Customer;


public:

    UserRole getRole() const override {return userRole;}
    std::variant<CustomerLevel, AdminLevel> getLevel() const override { return level;}


    bool setLevel(const std::variant<CustomerLevel, AdminLevel> &level) override {
        if (std::holds_alternative<CustomerLevel>(level)) {
            this->level = std::get<CustomerLevel>(level);
            return true;
        }
        return false;
    }


    Customer(unsigned int id, const std::string &name, const std::string &email, const std::string &hashedPassword)
        : User(id, name, email, hashedPassword){ level = CustomerLevel::BRONZE;}

    Customer(unsigned int id, const std::string &name, const std::string &email, const std::string &hashedPassword, const CustomerLevel& customerLevel)
        : User(id, name, email, hashedPassword){ level = customerLevel;}
};



#endif //CLIENT_H
