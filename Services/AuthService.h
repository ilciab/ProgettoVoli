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
        UserStruct login(const std::string&, const std::string&) const;
        UserStruct signIn(const std::string&, const std::string&, const std::string&) const;
        static std::string hashPassword(const std::string&);
        bool changeUserPassword(unsigned int userId, const std::string &oldPassword, const std::string &newPassword) const;
        void close() const;

        explicit AuthService(UserRepository &repo) : repo(repo) {}
};



#endif //AUTHSERVICE_H
