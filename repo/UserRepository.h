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
        std::vector<std::unique_ptr<User>> users;
        std::string customerPath, adminPath;
        IdGenerator idGen;
public:
    UserRepository(const std::string&, const std::string&);

    void load() override;
    void write() override;
    void add(const User&) override;
    unsigned int createCustomer(const std::string&, const std::string&, const std::string&, const CustomerLevel& customerLevel);
    void remove(int id) override;
    const User* getUserbyEmail(const std::string& email);
    std::vector<User> getAll() override;
    unsigned int* getById(int id) override;
};



#endif //USERREPOSITORY_H
