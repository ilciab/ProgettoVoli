//
// Created by ciabu on 23/09/2025.
//

#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H
#include <memory>

#include "RepositoryInterface.h"
#include "../domain/Customer.h"
#include "../util/IdGenerator.h"


class UserRepository : public RepositoryInterface<User> {

private:
        std::vector<std::unique_ptr<User>> users; //per gestione automatica e sennò si perde il rifeirmento
        std::string customerPath, adminPath;
        IdGenerator idGen;
public:
        UserRepository(const std::string &customerPath, const std::string &adminPath)
            : customerPath(customerPath),
              adminPath(adminPath) {
            UserRepository::load();
        }

    void load() override;
    void write() override;
    void add(const User&) override;
    unsigned int createCustomer(const std::string&, const std::string&, const std::string&, const CustomerLevel& customerLevel);
    void remove(int id) override;
    const User* getByEmail(const std::string& email) const;
    const User* getById(int id) const override;
    const std::vector<const User*> getAll() override;

    User *getById_internal(int id) override;
    void setUserName(unsigned int userId, const std::string & newName);
    void setUserEmail(unsigned int userId, const std::string & newEmail);
};



#endif //USERREPOSITORY_H
