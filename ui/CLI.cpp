//
// Created by ciabu on 24/09/2025.
//

#include "CLI.h"

#include <iostream>


void CLI::customerMenu() {
    unsigned int choice = 1;
    while (choice != 0) {
        std::cout << "Customer Panel:\n";
        std::cout << "";
        std::cout << "";
        std::cout << " 0 - Logout\n";


        std::cin >> choice;
        switch (choice) {
            case 0:
                userStruct = std::nullopt;
                return;
            default:
                std::cout << "Opzione non valida";
                break;
        }
    }
}


void CLI::adminMenu() {
    unsigned int choice = 1;
    while (choice != 0) {
        std::cout << "Admin Panel:\n";
        std::cout << " 1 - Modify and view Users\n";
        std::cout << " 2 - Modify and view Airports\n";
        std::cout << " 3 - Modify and view Flights\n";
        std::cout << " 4 - Modify and view Bookings\n";
        std::cout << " 0 - Logout\n";

        std::cin >> choice;
        switch (choice) {
            case 1:
                adminUsersMenu();
                break;
            case 2:
                adminAirportsMenu();
                break;
            case 0:
                userStruct = std::nullopt;
                return;
                break;
            default:
                std::cout << "Opzione non valida";
                break;
        }
    }
}

void CLI::printAllUsers() {
    UserRole userRole;
    AdminLevel adminLevel;
    CustomerLevel customerLevel;
    int level;
    std::cout << "User List:\n";

    std::vector<const User *> usersPointer = adminService.getAllUsers();
    for (const User *user: usersPointer) {
        userRole = user->getRole();
        switch (userRole) {
            case UserRole::Admin:
                adminLevel = std::get<AdminLevel>(user->getLevel());
                level = static_cast<int>(adminLevel);
                break;
            case UserRole::Customer:
                customerLevel = std::get<CustomerLevel>(user->getLevel());
                level = static_cast<int>(customerLevel);
                break;
        }
        std::cout << "ID:" << user->getId() << "\t";
        std::cout << "Email:" << user->getEmail() << "\t\t";
        std::cout << "Name:" << user->getName() << "\t";
        std::cout << "Level:" << level << "\t";
        std::cout << "Role:" << static_cast<int>(userRole) << "\n";
    }
}

void CLI::adminUsersMenu() {
    unsigned int selectedId = 1;
    while (selectedId != 0) {
        printAllUsers();
        std::cout << "Enter id of user to modify\n";
        std::cout << " 0 - Indietro\n";
        std::cin >> selectedId;
        const User *user = adminService.getUser(selectedId);

        if (user == nullptr) {
            std::cout << "L'utente con id: " << selectedId << " non esiste\n";
            continue;
        }
        bool running = true;
        while (running) {
            int choice;
            std::cout << "Utente Selezionato:\n";
            std::cout << "ID:" << user->getId() << "\t";
            std::cout << "Email:" << user->getEmail() << "\t";
            std::cout << "Name:" << user->getName() << "\t";
            std::cout << std::endl;
            std::cout << "1 - Modifica Nome\n";
            std::cout << "2 - Modifica Email\n";
            std::cout << "3 - Modifica Livello\n";
            std::cout << "4 - Elimina\n";
            std::cout << "0 - Indietro";

            std::cin >> choice;

            std::string newAttribute;
            switch (choice) {
                case 1:
                    std::cout<<"Inserisci nuovo nome: ";
                    std::cin >> newAttribute;
                    std::cout<<std::endl;
                    adminService.modifyUserName(user-> getId(), newAttribute);
                    break;
                case 2:
                    std::cout<<"Inserisci nuova email: ";
                    std::cin >> newAttribute;
                    std::cout<<std::endl;
                    adminService.modifyUserEmail(user-> getId(), newAttribute);
                    break;
                case 3:
                    std::cout<<"Da implementare";
                    //std::cout<<"Inserisci nuovo livello: ";
                    //std::cin >> newAttribute;
                    //adminService.modifyLevel(user-> getId(), newAttribute);
                    break;
                case 4:
                    std::cout<<"Utente eliminato\n";
                    adminService.deleteUser(user->getId());
                case 0:
                    running = false;
                    break;
                default:
                    std::cout << "Opzione non valida\n";
                    break;
            }

        }
    }
}

void CLI::printAllAirports() {

    std::cout << "Airport List:\n";
    std::vector<const Airport *> airportsPointer = adminService.getAllAirports();
    for (const Airport *airport : airportsPointer) {
        std::cout << "ID:" << airport->getId() << "\t";
        std::cout << "IATA:" << airport->getIata() << "\t\t";
        std::cout << "Nation:" << airport->getNation() << "\t";
        std::cout << "City:" <<  airport->getCity() << "\t";
        std::cout << "Name:" << airport->getName() << "\n";
    }
}
void CLI::adminAirportsMenu() {
    unsigned int choice = 1;
    while (choice != 0) {
        printAllAirports();
        std::cout << "Enter id of airport to modify\n";
        std::cout << " 0 - Indietro\n";
        std::cin >> choice;
        const Airport *airport = adminService.getAirport(choice);

        bool running = true;
        while (running) {
            int choice;
            std::cout << "Aeroporto selezionato:\n";
            std::cout << "ID:" << airport->getId() << "\t";
            std::cout << "IATA:" << airport->getIata() << "\t\t";
            std::cout << "Nation:" << airport->getNation() << "\t";
            std::cout << "City:" <<  airport->getCity() << "\t";
            std::cout << "Name:" << airport->getName() << "\n";
            std::cout << std::endl;
            std::cout << "1 - Nuovo Aeroporto\n";
            std::cout << "2 - Modifica IATA\n";
            std::cout << "3 - Modifica Nazione\n";
            std::cout << "4 - Modifica Città\n";
            std::cout << "5 - Modifica Nome\n";
            std::cout << "6 - Elimina\n";
            std::cout << "0 - Indietro";

            std::cin >> choice;

            std::string newAttribute;
            switch (choice) {
                case 1:
                    std::cout<<"Inserisci dati del nuovo areporto";
                    std::cout<<"IATA";
                    std::cout<<"Nazione";
                    std::cout<<"Città";
                    std::cout<<"Nome";
                    break;
                case 2:
                    std::cout<<"Inserisci nuovo IATA: ";
                    std::cin >> newAttribute;
                    std::cout<<std::endl;
                    adminService.modifyAirportIATA(airport->getId(), newAttribute);
                    break;
                case 3:
                    std::cout<<"Inserisci nuova Nazione: ";
                    std::cin >> newAttribute;
                    std::cout<<std::endl;
                    adminService.modifyAirportNation(airport->getId(), newAttribute);
                    break;
                case 4:
                    std::cout<<"Inserisci nuova Città: ";
                    std::cin >> newAttribute;
                    std::cout<<std::endl;
                    adminService.modifyAirportCity(airport->getId(), newAttribute);
                    break;
                case 5:
                    std::cout<<"Inserisci nuovo Nome: ";
                    std::cin >> newAttribute;
                    std::cout<<std::endl;
                    adminService.modifyAirportName(airport->getId(), newAttribute);
                    break;
                case 6:
                    std::cout<<"";//todo
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    std::cout << "Opzione non valida\n";
                    break;
            }

        }
    }
}


void CLI::loginMenu() {
    bool running = true;
    while (running) {
        int choice;
        std::cout << "Benvenuto su Ciab Booking Service\n\n";
        std::cout << "1 - Accedi\n";
        std::cout << "2 - Registrati\n\n";
        std::cout << "0 - Esci\n";

        std::cin >> choice;

        switch (choice) {
            case 1:
                userStruct = login();
                break;
            case 2:
                userStruct = signIn();
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Opzione non valida\n";
                break;
        }

        if (!userStruct.has_value())
            continue;
        if (userStruct->role == UserRole::Customer)
            customerMenu();
        else if (userStruct->role == UserRole::Admin)
            adminMenu();
    }
}

std::optional<UserStruct> CLI::login() {
    std::string email, password;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Password: ";
    std::cin >> password;

    std::optional<UserStruct> result = authService.login(email, password);

    if (result.has_value()) {
        std::cout << "Benvenuto!\n";
    } else
        std::cout << "Combinazione mail/password errata, riprova\n";

    return result;
}


std::optional<UserStruct> CLI::signIn() {
    std::string name, email, password;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Password: ";
    std::cin >> password;
    std::optional<UserStruct> result = authService.signIn(name, email, password);
    if (!result.has_value())
        std::cout << "Qualcosa è andato storto";
    return result;
}
