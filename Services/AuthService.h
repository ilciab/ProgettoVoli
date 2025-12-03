//
// Created by ciabu on 25/09/2025.
//

#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H
#include "../Repositories/UserRepository.h"


struct UserStruct;

class AuthService {
    private:
        UserRepository& repo;

    public:
        std::optional<UserStruct> login(const std::string&, const std::string&);
        std::optional<UserStruct> signIn(const std::string&, const std::string&, const std::string&);
        std::string hashPassword(const std::string&);

        void close();

        explicit AuthService(UserRepository &repo) : repo(repo) {}
};



#endif //AUTHSERVICE_H
