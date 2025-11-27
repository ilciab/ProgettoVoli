//
// Created by ciabu on 24/09/2025.
//

#include "CLI.h"

#include <iostream>

#include "../Utils/RepositoryUtils.h"

int CLI::stringToPositiveInteger(const std::string &string) {
    try {
        int result = std::stoi(string);

        if (result < 0) {
            std::cout << "Input non valido (negativo)!\n";
            return -1;
        }

        return result;
    } catch (...) {
        std::cout << "Input non valido (non un numero)!\n";
        return -1;
    }
}

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
            case 3:
                adminFlightsMenu();
            case 0:
                userStruct = std::nullopt;
                return;
            default:
                std::cout << "Opzione non valida";
                break;
        }
    }
}

unsigned int CLI::printAllUsers() const {
    UserRole userRole;
    AdminLevel adminLevel;
    CustomerLevel customerLevel;
    unsigned int level;
    unsigned int usersNumber;
    std::cout << "Lista Utenti:\n";

    std::vector<const User *> usersPointer = adminService.getAllUsers();
    usersNumber = usersPointer.size();

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
        std::cout << "ID: " << user->getId() << "\t";
        std::cout << "Email: " << user->getEmail() << "\t";
        std::cout << "Nome: " << user->getName() << "\t";
        std::cout << "Livello: " << level << "\t";
        std::cout << "Ruolo: " << static_cast<int>(userRole) << "\t";
        std::cout << std::endl;

        //todo level
    }
    return usersNumber;

    //fixme fare come printall airports se non c'è nessuno
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
                    std::cout << "Inserisci nuovo nome: ";
                    std::cin >> newAttribute;
                    std::cout << std::endl;
                    adminService.modifyUserName(user->getId(), newAttribute);
                    break;
                case 2:
                    std::cout << "Inserisci nuova email: ";
                    std::cin >> newAttribute;
                    std::cout << std::endl;
                    adminService.modifyUserEmail(user->getId(), newAttribute);
                    break;
                case 3:
                    std::cout << "Da implementare";
                    //std::cout<<"Inserisci nuovo livello: ";
                    //std::cin >> newAttribute;
                    //adminService.modifyLevel(user-> getId(), newAttribute);
                    break;
                case 4:
                    std::cout << "Utente eliminato\n";
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

unsigned int CLI::printAllFlights() const {
    std::vector<const Flight *> flightsPointer = adminService.getAllFlights();
    unsigned int flightsNumber = flightsPointer.size();
    if (flightsPointer.empty())
        return flightsNumber;

    std::cout << "Lista Voli:\n";
    for (const Flight *flight: flightsPointer) {
        std::string departureAirportName = adminService.getAirport(flight->getDepartureAirportId())->getName();
        std::string arrivalAirportName = adminService.getAirport(flight->getArrivalAirportId())->getName();

        std::cout << "ID:" << flight->getId() << "\t";
        std::cout << "Aeroporto di Partenza" << departureAirportName << "\t";
        std::cout << "Aeroporto di Arrivo" << arrivalAirportName << "\t";
        std::cout << "Orario di Partenza: " << timePointToString(flight->getDepartureTime()) << "\t";
        std::cout << "Orario di Arrivo: " << timePointToString(flight->getArrivalTime()) << "\t";
        std::cout << "Prezzo: $" << flight->getPrice() << "\t";
        std::cout << "Posti totali: " << flight->getTotalSeats() << "\t";
        std::cout << "Posti occupati: " << flight->getBookedSeats() << "\t";
    }
    return flightsNumber;
}

unsigned int CLI::printAllAirports() const {
    std::vector<const Airport *> airportsPointer = adminService.getAllAirports();
    unsigned int airportsNumber = airportsPointer.size();
    if (airportsPointer.empty())
        return airportsNumber;

    std::cout << "Lista Aeroporti:\n";
    for (const Airport *airport: airportsPointer) {
        std::cout << "ID: " << airport->getId() << "\t";
        std::cout << "IATA: " << airport->getIata() << "\t";
        std::cout << "Nazione: " << airport->getNation() << "\t";
        std::cout << "Città: " << airport->getCity() << "\t";
        std::cout << "Nome: " << airport->getName() << "\t";
        std::cout << std::endl;
    }
    return airportsNumber;
}


void CLI::createAirportWizard() {
    std::cin.ignore();
    std::string iata, nation, city, name;

    std::cout << "--- CREAZIONE AEROPORTO ---\n";

    std::cout << "Inserire dati nuovo aeroporto:\n";

    do {
        std::string userInput;
        std::cout << "IATA (3 caratteri): ";
        std::getline(std::cin, userInput);
        std::cout << std::endl;
        iata = iataFormat(userInput);
        if (iata == "")
            std::cout << "Errore: IATA deve avere esattemente 3 caratteri!\n";
    } while (iata == "");

    std::cout << "Nazione: ";
    std::getline(std::cin, nation);
    std::cout << "Città: ";
    std::getline(std::cin, city);
    std::cout << "Nome: ";
    std::getline(std::cin, name);

    bool result = adminService.createAirport(iata, nation, city, name);

    if (result)
        std::cout<<"Aeroporto creato con successo!\n";
    else
        std::cout << "Errore: Impossibile creare aeroporto (IATA duplicato?)\n";

    std::cout << "---------------------------\n";
}

void CLI::manageSingleAirport(const unsigned int id) {


    bool editing = true;
    while (editing) {
        const Airport *airport = adminService.getAirport(id);
        if (airport == nullptr) {
            std::cout << "Aeroporto con id: " << id << " non trovato\n";
            return;
        }
        std::cout << "Aeroporto selezionato:\n";
        std::cout << "ID:" << airport->getId() << "\t";
        std::cout << "IATA:" << airport->getIata() << "\t\t";
        std::cout << "Nation:" << airport->getNation() << "\t";
        std::cout << "City:" << airport->getCity() << "\t";
        std::cout << "Name:" << airport->getName() << "\n";
        std::cout << std::endl;
        std::cout << "1 - Modifica IATA\n";
        std::cout << "2 - Modifica Nazione\n";
        std::cout << "3 - Modifica Città\n";
        std::cout << "4 - Modifica Nome\n";
        std::cout << "5 - Elimina\n";
        std::cout << "0 - Indietro\n";

        char subChoice;
        std::cin >> subChoice;
        std::string userInput;
        std::cin.ignore();
        switch (subChoice) {
            case '1': {
                std::string formattedIata;
                do {
                    std::cout << "Inserisci nuovo IATA (3 caratteri): ";
                    std::getline(std::cin, userInput);
                    std::cout << std::endl;
                    formattedIata = iataFormat(userInput);
                    if (formattedIata == "")
                        std::cout << "Il codice IATA deve avere esattemente 3 caratteri!\n";
                } while (formattedIata == "");
                adminService.modifyAirportIATA(airport->getId(), formattedIata);
                break;
            }
            case '2':
                std::cout << "Inserisci nuova Nazione: ";
                std::getline(std::cin, userInput);
                std::cout << std::endl;
                adminService.modifyAirportNation(airport->getId(), userInput);
                break;
            case '3':
                std::cout << "Inserisci nuova Città: ";
                std::getline(std::cin, userInput);
                std::cout << std::endl;
                adminService.modifyAirportCity(airport->getId(), userInput);
                break;
            case '4':
                std::cout << "Inserisci nuovo Nome: ";
                std::getline(std::cin, userInput);
                std::cout << std::endl;
                adminService.modifyAirportName(airport->getId(), userInput);
                break;
            case '5':
                std::cout << "Aeroporto eliminato!\n";
                adminService.deleteAirport(id);
                editing = false;
                break;
            case '0':
                editing = false;
                break;
            default:
                std::cout << "Opzione non valida\n";
                break;
        }
    }
}


void CLI::adminAirportsMenu() {
    std::string choice;
    while (true) {
        const unsigned int airportsNumber = printAllAirports();
        std::cout << "Trovati " << airportsNumber << " aeroporti.\n";
        if (airportsNumber == 0)
            std::cout << "Premere n per creare un nuovo aeroporto\n";
        else
            std::cout << "Inserire Id dell'areoporto da modificare o premere n per crearne uno nuovo\n";
        std::cout << " 0 - Indietro\n";
        std::cin >> choice;

        if (choice == "0") return;

        if (choice == "n") {
            createAirportWizard();
        } else {
            int id = stringToPositiveInteger(choice);

            if (id == -1) {
                std::cout << "Errore: ID non valido o input errato.\n\n";
                continue;
            }

            manageSingleAirport(id);
        }
    }
}



void CLI::adminFlightsMenu(){

}


    void CLI::loginMenu()
    {
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
        authService.close();
        adminService.close();
    }

    std::optional<UserStruct> CLI::login()
    {
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

    std::string CLI::iataFormat(std::string iata)
    {
        if (iata.length() != 3)
            return "";

        for (char &c: iata) {
            if (!std::isalpha(c))
                return "";
            c = std::toupper(c);
        }
        return iata;
    }


    std::optional<UserStruct> CLI::signIn()
    {
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
