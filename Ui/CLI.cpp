//
// Created by ciabu on 24/09/2025.
//

#include "CLI.h"

#include <iostream>

#include "../Utils/RepositoryUtils.h"


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

void CLI::printAllUsers(const std::vector<const User *> &users) const {
    UserRole userRole;
    AdminLevel adminLevel;
    CustomerLevel customerLevel;
    unsigned int level;
    unsigned int usersNumber;
    std::cout << "Lista Utenti:\n";

    for (const User *user: users) {
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

    //fixme fare come printall airports se non c'è nessuno
}

void CLI::adminUsersMenu() {
    unsigned int selectedId = 1;
    while (selectedId != 0) {
        std::vector<const User *> users = adminService.getAllUsers();
        printAllUsers(users);
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
            } //todo come adminmenu
        }
    }
}

void CLI::printAllAirports(const std::vector<const Airport *> &airports) const {
    std::cout << "Lista Aeroporti:\n";
    for (const Airport *airport: airports) {
        std::cout << "ID: " << airport->getId() << "\t";
        std::cout << "IATA: " << airport->getIata() << "\t";
        std::cout << "Nazione: " << airport->getNation() << "\t";
        std::cout << "Città: " << airport->getCity() << "\t";
        std::cout << "Nome: " << airport->getName() << "\t";
        std::cout << std::endl;
    }
}

void CLI::printAllFlights(const std::vector<const Flight *> &flights) const {
    std::cout << "Lista Voli:\n";
    for (const Flight *flight: flights) {
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
        std::cout << "Aeroporto creato con successo!\n";
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

void CLI::createFlightWizard() {
    std::cin.ignore();
    int departureAirportId, arrivalAirportId, price, totalSeats;
    std::string departureAirportIdStr, arrivalAirportIdStr, priceStr, totalSeatsStr, departureTimeStr,
            arrivalTimeStr;
    std::chrono::system_clock::time_point departureTime, arrivalTime;
    std::optional<std::chrono::system_clock::time_point> optTime;

    std::cout << "--- CREAZIONE VOLO ---\n";

    std::cout << "Inserire dati nuovo Volo:\n";

    do {
        std::cout << "Id aeroporto di partenza: ";
        std::getline(std::cin, departureAirportIdStr);
        departureAirportId = stringToPositiveInteger(departureAirportIdStr);
        if (departureAirportId == -1)
            std::cout << "Errore: input non valido\n";
    } while (departureAirportId == -1);

    do {
        std::cout << "Id aeroporto di arrivo: ";
        std::getline(std::cin, arrivalAirportIdStr);
        arrivalAirportId = stringToPositiveInteger(arrivalAirportIdStr);
        if (arrivalAirportId == -1)
            std::cout << "Errore: input non valido\n";
    } while (arrivalAirportId == -1);

    do {
        std::cout << "Orario di partenza: ";
        std::getline(std::cin, departureTimeStr);
        optTime = stringToTimePoint(departureTimeStr);
        if (optTime.has_value())
            departureTime = optTime.value();
        else
            std::cout << "Errore: input non valido\n";
    } while (!optTime.has_value());

    do {
        std::cout << "Orario di arrivo: ";
        std::getline(std::cin, arrivalTimeStr);
        optTime = stringToTimePoint(arrivalTimeStr);
        if (optTime.has_value())
            departureTime = optTime.value();
        else
            std::cout << "Errore: input non valido\n";
    } while (!optTime.has_value());

    do {
        std::cout << "Posti totali: ";
        std::getline(std::cin, totalSeatsStr);
        totalSeats = stringToPositiveInteger(totalSeatsStr);
        if (totalSeats == -1)
            std::cout << "Errore: input non valido\n";
    } while (totalSeats == -1);
    std::cout << "Prezzo: ";


    bool result = adminService.createFlight(arrivalAirportId, departureAirportId, departureTime, arrivalTime, price, totalSeats);

    if (result)
        std::cout << "Volo creato con successo!\n";
    else
        std::cout << "Errore: Impossibile creare il volo\n";

    std::cout << "---------------------------\n";
}

void CLI::manageSingleFlight(const unsigned int id) {
}

void CLI::adminAirportsMenu() {
    std::string choice;
    while (true) {
        std::vector<const Airport *> airports = adminService.getAllAirports();
        const unsigned int airportsNumber = airports.size();
        std::cout << "Trovati " << airportsNumber << " aeroporti.\n";
        if (airportsNumber == 0)
            std::cout << "Premere n per creare un nuovo aeroporto\n";
        else {
            printAllAirports(airports);
            std::cout << "Inserire Id dell'areoporto da modificare o premere n per crearne uno nuovo\n";
        }
        std::cout << " 0 - Indietro\n";
        std::cin >> choice;

        if (choice == "0") return;

        if (choice == "n") {
            createAirportWizard();
        } else {
            const int id = stringToPositiveInteger(choice);

            if (id == -1) {
                std::cout << "Errore: ID non valido o input errato.\n\n";
                continue;
            }

            manageSingleAirport(id);
        }
    }
}

void CLI::adminFlightsMenu() {
    std::string choice;
    while (true) {
        std::vector<const Flight *> flights = adminService.getAllFlights();
        unsigned int flightsNumber = flights.size();
        std::cout << "Trovati " << flightsNumber << " voli.\n";
        if (flightsNumber == 0)
            std::cout << "Premere n per creare un nuovo volo\n";
        else {
            printAllFlights(flights);
            std::cout << "Inserire Id del volo da modificare o premere n per crearne uno nuovo\n";
        }
        std::cout << " 0 - Indietro\n";
        std::cin >> choice;

        if (choice == "0") return;

        if (choice == "n") {
            createFlightWizard();
        } else {
            int id = stringToPositiveInteger(choice);

            if (id == -1) {
                std::cout << "Errore: ID non valido o input errato.\n\n";
                continue;
            }

            manageSingleFlight(id);
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
    authService.close();
    adminService.close();
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

std::string CLI::iataFormat(std::string iata) {
    if (iata.length() != 3)
        return "";

    for (char &c: iata) {
        if (!std::isalpha(c))
            return "";
        c = std::toupper(c);
    }
    return iata;
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
