
#ifndef PROGETTOVOLI_USERFACTORY_H
#define PROGETTOVOLI_USERFACTORY_H
#include <memory>
#include "../Domain/User.h"
#include "../Domain/Customer.h"
#include "../Domain/Admin.h"

class UserFactory {
public:
    virtual ~UserFactory() = default;
    virtual std::unique_ptr<User> createUser(unsigned int id, const std::string& name,
                                           const std::string& email, const std::string& pass) const = 0;
};

class CustomerFactory final : public UserFactory {
public:
    std::unique_ptr<User> createUser(unsigned int id, const std::string& name,
                                     const std::string& email, const std::string& pass) const override {
        return std::make_unique<Customer>(id, name, email, pass);
    }
};

class AdminFactory final : public UserFactory {
public:
    std::unique_ptr<User> createUser(unsigned int id, const std::string& name,
                                   const std::string& email, const std::string& pass) const override {
        return std::make_unique<Admin>(id, name, email, pass);
    }
};


#endif //PROGETTOVOLI_USERFACTORY_H