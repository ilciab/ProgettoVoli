//
// Created by ciabu on 23/09/2025.
//

#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H
#include <memory>

#include "RepositoryInterface.h"
#include "../domain/User.h"
#include "../util/IdGenerator.h"


class UserRepository : public RepositoryInterface<User> {

private:
        std::vector<std::unique_ptr<User>> users;
        std::string path;
        IdGenerator idGen;
public:
    UserRepository(const std::string&);

    void load() override;
    void save() override;
    void add(const User&) override;
    unsigned int createClient(const std::string&, const std::string&, const std::string&);
    void remove(int id) override;
    const User* getUserbyEmail(const std::string& email);
    std::vector<User> getAll() override;
    unsigned int* getById(int id) override;
};



#endif //USERREPOSITORY_H
