//
// Created by ciabu on 22/09/2025.
//

#ifndef USER_H
#define USER_H
#include <cstdint>
#include <string>
#include <typeindex>


class User {
    protected:
        unsigned int id;
        std::string name, email, hashedPassword;

public:
    User(unsigned int id, const std::string& name, const std::string& email, const std::string& hashedPassword);
    const unsigned int& getId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& gethashedPassword() const;

};



#endif //USER_H
