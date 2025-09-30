//
// Created by ciabu on 24/09/2025.
//

#ifndef CLI_H
#define CLI_H
#include "../domain/User.h"
#include "../service/AuthService.h"


class CLI {

    private:
        unsigned int loggedUserID;
        AuthService& authService;


    public:
        CLI(AuthService&);

        void setLoggedID(unsigned int login);
        void menu();
        void signIn();
        void login();
};



#endif //CLI_H
