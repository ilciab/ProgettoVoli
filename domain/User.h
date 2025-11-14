//
// Created by ciabu on 22/09/2025.
//

#ifndef USER_H
#define USER_H
#include <cstdint>
#include <string>
#include <typeindex>
#include <variant>

#include "../enums/AdminLevel.h"
#include "../enums/CustomerLevel.h"
#include "../enums/UserRole.h"

class User {
protected:
    std::variant<CustomerLevel, AdminLevel> level;
    unsigned int id;
    std::string name, email, hashedPassword;

public:
    virtual ~User() = default;

    virtual UserRole getRole() const = 0;

    virtual std::variant<CustomerLevel, AdminLevel> getLevel() const = 0;
    const unsigned int &getId() const { return id; }
    const std::string &getName() const { return name; }
    const std::string &getEmail() const { return email; }
    const std::string &getHashedPassword() const { return hashedPassword; }

    User(unsigned int id, const std::string &name, const std::string &email, const std::string &hashed_password)
        : id(id),
          name(name),
          email(email),
          hashedPassword(hashed_password) {
    }
};


#endif //USER_H
