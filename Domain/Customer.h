

#ifndef CLIENT_H
#define CLIENT_H
#include "User.h"


class Customer : public User {

private:
    UserRole userRole = UserRole::Customer;


public:

    UserRole getRole() const override {return userRole;}



    Customer(unsigned int id, const std::string &name, const std::string &email, const std::string &hashedPassword)
        : User(id, name, email, hashedPassword){}
};



#endif //CLIENT_H
