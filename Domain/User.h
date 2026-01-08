
#ifndef USER_H
#define USER_H
#include <string>
#include <variant>

#include "../Enums/UserRole.h"

class User {
protected:
    const unsigned int id;
    std::string name, email, hashedPassword;

public:
    virtual ~User() = default;

    virtual UserRole getRole() const = 0;

    unsigned int getId() const { return id; }
    const std::string &getName() const { return name; }
    const std::string &getEmail() const { return email; }
    const std::string &getHashedPassword() const { return hashedPassword; }

    void setName(const std::string &name) { this->name = name; }
    void setEmail(const std::string &email) { this->email = email; }
    void setHashedPassword(const std::string &hashedPassword) { this->hashedPassword = hashedPassword; }

    User(unsigned int id, const std::string &name, const std::string &email, const std::string &hashed_password)
        : id(id),
          name(name),
          email(email),
          hashedPassword(hashed_password) {
    }
};


#endif //USER_H
