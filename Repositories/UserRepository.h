//
// Created by ciabu on 23/09/2025.
//

#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H
#include <memory>

#include "RepositoryInterface.h"
#include "../Domain/Customer.h"
#include "../Utils/IdGenerator.h"


class UserRepository : public RepositoryInterface<User> {
    std::vector<std::unique_ptr<User> > users; //per gestione automatica e sennò si perde il rifeirmento
    std::string customerPath, adminPath;
    IdGenerator idGen;
    User *getById_internal(unsigned int id) override;

public:
    UserRepository(const std::string &customerPath, const std::string &adminPath)
        : customerPath(customerPath),
          adminPath(adminPath) {
        UserRepository::load();
    }

    void createDefaultAdmin(unsigned int largestId);
    void load() override;
    void write() override;
    void remove(unsigned int id) override;

    unsigned int createCustomer(const std::string &name, const std::string &email, const std::string &hashedPassword);
    unsigned int createAdmin(const std::string &name, const std::string &email, const std::string &hashedPassword);

    const User *getByEmail(const std::string &email) const;
    const User *getById(unsigned int id) const override;
    std::vector<const User *> getAll() override;

    void setUserName(unsigned int userId, const std::string &newName);
    void setUserEmail(unsigned int userId, const std::string &newEmail);
    void setUserPassword(unsigned int userId, const std::string &newHahsedPassword);
};


#endif //USERREPOSITORY_H
