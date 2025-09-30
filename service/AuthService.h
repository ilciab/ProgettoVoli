//
// Created by ciabu on 25/09/2025.
//

#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H
#include "../repo/UserRepository.h"


class AuthService {
    private:
        UserRepository& repo;

    public:
        std::optional<unsigned int> login(const std::string&, const std::string&);
        std::optional<unsigned int> signIn(const std::string&, const std::string&, const std::string&);
        std::string hashPassword(const std::string&);

        void close();

        explicit AuthService(UserRepository&);
};



#endif //AUTHSERVICE_H
