//
// Created by ciabu on 24/09/2025.
//

#include "CLI.h"

#include <iostream>


CLI::CLI(AuthService& authService): authService(authService) {}


void CLI::menu(){
    int choice = 1;

    while (choice != 0){
        std::cout<<"Benvenuto su Ciab Booking Service\n\n";
        std::cout<<"1 - Accedi\n";
        std::cout<<"2 - Registrati\n\n";
        std::cout<<"0 - Esci\n";

        std::cin>>choice;

        switch (choice) {
            case 1:
                login(); //setLoggedId(login())
                break;
            case 2:
                signIn();
                break;
            default:
                authService.close();
        }
    }
}

void CLI::login() {

    std::string email, password;
    std::cout<<"Email: ";
    std::cin>>email;
    std::cout<<"Password: ";
    std::cin>>password;

    std::optional<unsigned int> result =  authService.login(email,password);

    if (result.has_value()) {
        loggedUserID = result.value();
        std::cout << "Benvenuto!\n";
    }
    else
        std::cout<<"Combinazione mail/password errata, riprova\n";

}



void CLI::signIn() {
    std::string name, email, password;
    std::cout<<"Name: ";
    std::cin>>name;
    std::cout<<"Email: ";
    std::cin>>email;
    std::cout<<"Password: ";
    std::cin>>password;
    std::optional<unsigned int> result = authService.signIn(name,email,password);
    if (result.has_value()) {
        loggedUserID = result.value();
    }
    else
        std::cout<<"Qualcosa è andato storto";
}

void CLI::setLoggedID(unsigned int loggedUserID) {
    this->loggedUserID = loggedUserID;
}



