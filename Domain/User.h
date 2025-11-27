//
// Created by ciabu on 22/09/2025.
//

#ifndef USER_H
#define USER_H
#include <cstdint>
#include <string>
#include <typeindex>
#include <variant>

#include "../Enums/AdminLevel.h"
#include "../Enums/CustomerLevel.h"
#include "../Enums/UserRole.h"

class User {
protected:
    const unsigned int id;
    std::string name, email, hashedPassword;

public:
    virtual ~User() = default;

    virtual UserRole getRole() const = 0;

    virtual std::variant<CustomerLevel, AdminLevel> getLevel() const = 0;

    unsigned int getId() const { return id; }
    const std::string &getName() const { return name; }
    const std::string &getEmail() const { return email; }
    const std::string &getHashedPassword() const { return hashedPassword; }

    void setName(const std::string &name) { this->name = name; }
    void setEmail(const std::string &email) { this->email = email; }
    void setHashedPassword(const std::string &hashedPassword) { this->hashedPassword = hashedPassword; }


/**
 * @brief Tenta di aggiornare il livello dell'utente.
 * * @return @c true se il tipo di livello passato corrisponde al tipo di utente (es. CustomerLevel per un Customer).
 * @return @c false se il tipo non è compatibile.
 */
    virtual bool setLevel(const std::variant<CustomerLevel, AdminLevel> &level) = 0;

    User(unsigned int id, const std::string &name, const std::string &email, const std::string &hashed_password)
        : id(id),
          name(name),
          email(email),
          hashedPassword(hashed_password) {
    }
};


#endif //USER_H
