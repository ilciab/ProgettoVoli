//
// Created by ciabu on 24/09/2025.
//

#include "CLI.h"

#include <iostream>
#include <format>

#include "../Utils/RepositoryUtils.h"


std::string CLI::timepointToString(std::chrono::system_clock::time_point tp) const {
    std::string timeDateStr = std::format("{:%Y-%m-%d %H:%M}", tp);
    return timeDateStr;
}

void CLI::clearScreen() const {
    std::cout << "\033[2J\033[1;1H\033[3J" << std::flush;
}

void CLI::waitInput() const {
    std::cout << "Premi invio per continuare\n";
    std::cin.ignore();
    std::cin.get();
}

void CLI::customerBookingsMenu() {
    clearScreen();
    std::vector<const Flight *> flights = customerService.getAllFlights();
    const Flight *selectedFlight;
    int selectedFlightId, ticketsNumber;
    std::string choice;

    if (flights.empty()) {
        std::cout << "Errore: non sono presenti voli nel database, torna più tardi\n";
        waitInput();
        return;
    }
    clearScreen();
    printAllFlights(flights);

    std::cin.ignore();
    do {
        std::string selectedFlightIdStr;
        std::cout << "Id volo da prenotare: ";
        std::getline(std::cin, selectedFlightIdStr);
        selectedFlightId = stringToPositiveInteger(selectedFlightIdStr);
        if (selectedFlightId == -1)
            std::cout << "Errore: input non valido\n";
        selectedFlight = adminService.getFlight(selectedFlightId);
        if (selectedFlight == nullptr) {
            std::cout << "Errore: non esiste un volo con quell'id\n";
        }
    } while (selectedFlightId == -1 or selectedFlight == nullptr);

    unsigned int freeSeats = selectedFlight->getTotalSeats() - selectedFlight->getBookedSeats();

    do {
        std::cout << "Numero di biglietti da acquistare: ";
        std::string input;
        std::getline(std::cin, input);
        ticketsNumber = stringToPositiveInteger(input);
        if (ticketsNumber == -1)
            std::cout << "Errore: input non valido\n";
        if (ticketsNumber > freeSeats)
            std::cout << "Errore: sono rimasti solo " << freeSeats << "posti\n";
    } while (ticketsNumber == -1 or ticketsNumber > freeSeats);

    std::cout << "Totale: $" << adminService.getFlight(selectedFlightId)->getPrice() * ticketsNumber << std::endl;
    std::cout << "Acquistare? Y/N";
    std::cin >> choice;
    if (choice == "y" or choice == "Y") {
        bool bookResult = customerService.book(userStruct.id, selectedFlightId, ticketsNumber);
        if (bookResult == true)
            std::cout << "Volo aquistato.\n";
        else
            std::cout << "Errore nell'acquistare il volo\n";
    } else
        std::cout << "Volo non aquistato.\n";
    waitInput();
}

void CLI::customerMenu() {
    while (true) {
        clearScreen();
        std::string strChoice;
        std::cout << "--- MENU PRINCIPALE ---\n";
        std::cout << "1 - Prenota volo\n";
        std::cout << "2 - Modifica Profilo\n";
        std::cout << "3 - Le mie prenotazioni\n";

        std::cout << "0 - Logout\n";

        std::cin >> strChoice;
        int choice = stringToPositiveInteger(strChoice);
        if (choice == -1)
            continue;
        switch (choice) {
            case 1: {
                customerBookingsMenu();
                break;
            }

            case 2: {
                customerProfileMenu();
                break;
            }

            case 3: {
                std::vector<const Reservation *> reservations = customerService.getAllReservations();
                if (reservations.size() == 0) {
                    std::cout << "Errore: non sono prenotazioni a tuo nome\n";
                    waitInput();
                    break;
                }
                clearScreen();
                printAllUserReservations(reservations, userStruct.id);
                waitInput();
                break;
            }

            case 0:
                userStruct = {};
                return;
            default:
                break;
        }
    }
}

void CLI::customerProfileMenu() {
    clearScreen();
    while (true) {
        std::string strChoice;
        std::cout << "----- MENU UTENTE -----\n";
        std::cout << "1 - Modifica nome\n";
        std::cout << "2 - Modifica email\n";
        std::cout << "3 - Modifica password\n";
        std::cout << "0 - Indietro\n";
        std::cout << "----------------------\n";
        std::cin >> strChoice;
        int choice = stringToPositiveInteger(strChoice);
        if (choice == -1)
            continue;

        switch (choice) {
            case 1: {
                std::string newName;
                std::cout << "Inserisci nuovo nome: ";
                std::cin >> newName;
                customerService.changeUserName(userStruct.id, newName);
                std::cout << "Nome modificato correttamente\n";
                waitInput();
                break;
            }
            case 2: {
                std::string newEmail;
                std::cout << "Inserisci nuova email: ";
                std::cin >> newEmail;
                customerService.changeUserName(userStruct.id, newEmail);
                std::cout << "Email modificata correttamente\n";
                waitInput();
                break;
            }
            case 3: {
                std::string oldPassword, newPassword;
                std::cout << "Inserisci vecchia password: ";
                std::cin >> oldPassword;
                std::cout << "Inserisci nuova password: ";
                std::cin >> newPassword;
                bool result = customerService.changeUserPassword(userStruct.id, oldPassword, newPassword);
                if (result)
                    std::cout << "Password cambiata correttamente\n";
                else
                    std::cout << "Errore nel cambio della password\n";
                waitInput();
                break;
            }
            case 0:
                return;
            default:
                break;
        }
    }
}

void CLI::adminMenu() {
    unsigned int choice = 1;
    while (choice != 0) {
        clearScreen();
        std::cout << "----- MENU ADMIN -----\n";
        std::cout << " 1 - Modify and view Users\n";
        std::cout << " 2 - Modify and view Airports\n";
        std::cout << " 3 - Modify and view Flights\n";
        std::cout << " 4 - Modify and view Bookings\n";
        std::cout << " 0 - Logout\n";
        std::cout << "----------------------\n";
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
                userStruct = {};
                return;
            default:
                std::cout << "Opzione non valida";
                break;
        }
    }

    //todo cambiare tipo choice (un po' dappertutto)
}

void CLI::printAllUsers(const std::vector<const User *> &users) const {
    UserRole userRole;
    std::cout << "----- LISTA UTENTI -------\n";

    for (const User *user: users) {
        userRole = user->getRole(); //todo aggiustare per l'admin (ce ne è solo uno) (ne rimarrà solo uno!)
        std::cout << "ID: " << user->getId() << "\t";
        std::cout << "Email: " << user->getEmail() << "\t";
        std::cout << "Nome: " << user->getName() << "\t";
        std::cout << "Ruolo: " << static_cast<int>(userRole) << "\t";
        std::cout << std::endl;
        std::cout << "--------------------------\n";
    }

    //todo fixme fare come printall airports se non c'è nessuno
}

void CLI::adminUsersMenu() {
    unsigned int selectedId = 1;
    while (selectedId != 0) {
        std::vector<const User *> users = adminService.getAllUsers();
        clearScreen();
        printAllUsers(users);
        std::cout << "Inserisci l'id dell'utente da modificare\n";
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
            std::cout << "3 - Elimina\n";
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
    std::cout << "---- LISTA AEROPORTI -----\n";
    for (const Airport *airport: airports) {
        std::cout << "ID: " << airport->getId() << "\t";
        std::cout << "IATA: " << airport->getIata() << "\t";
        std::cout << "Nazione: " << airport->getNation() << "\t\t";
        std::cout << "Città: " << airport->getCity() << "\t\t";
        std::cout << "Nome: " << airport->getName() << "\t";
        std::cout << std::endl;
    }
    std::cout << "--------------------------\n";
}

void CLI::printAllFlights(const std::vector<const Flight *> &flights) const {
    std::cout << "------- LISTA VOLI -------\n";
    std::cout << std::endl;
    for (const Flight *flight: flights) {
        std::string departureAirportName = adminService.getAirport(flight->getDepartureAirportId())->getName();
        std::string arrivalAirportName = adminService.getAirport(flight->getArrivalAirportId())->getName();
        std::cout << "ID:" << flight->getId() << "\t";
        std::cout << std::endl;
        std::cout << departureAirportName << " -> " << arrivalAirportName;
        std::cout << std::endl;
        std::cout << "Partenza: " << timePointToString(flight->getDepartureTime()) << "\t";
        std::cout << std::endl;
        std::cout << "Arrivo: " << timePointToString(flight->getArrivalTime()) << "\t";
        std::cout << std::endl;
        std::cout << "Prezzo: $" << flight->getPrice() << "\t";
        std::cout << "Posti totali: " << flight->getTotalSeats() << "\t";
        std::cout << "Posti occupati: " << flight->getBookedSeats() << "\t";
        std::cout << std::endl << std::endl;
    }
}

void CLI::printAllUserReservations(const std::vector<const Reservation *> &reservations, unsigned int userId) const {
    std::cout << "--- LISTA PRENOTAZIONI ---\n";
    std::cout << std::endl;
    for (const Reservation *reservation: reservations) {
        const Airport *departureAirport, *arrivalAirport;
        const Flight *flight = customerService.getFlight(reservation->getFlightId());
        departureAirport = customerService.getAirport(flight->getDepartureAirportId());
        arrivalAirport = customerService.getAirport(flight->getArrivalAirportId());
        std::cout << "ID:" << reservation->getId() << std::endl;
        std::cout << "Volo: " << departureAirport->getName() << " --> " << arrivalAirport->getName() << std::endl;
        std::cout << "Orario: " << timepointToString(flight->getDepartureTime()) << " --> " << timePointToString(
            flight->getArrivalTime()) << std::endl;
        std::cout << std::endl;
        std::cout << "---------------------------\n";
    }
};

void CLI::createAirportWizard() {
    clearScreen();
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
        clearScreen();
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
                adminService.deleteAirport(id);
                std::cout << "Aeroporto eliminato!\n";
                editing = false;
                waitInput();
                break;
            case '0':
                editing = false;
                break;
            default:
                break;
        }
    }
}

void CLI::createFlightWizard() {
    clearScreen();
    std::cin.ignore();
    int departureAirportId, arrivalAirportId, price, totalSeats;
    std::string departureAirportIdStr, arrivalAirportIdStr, priceStr, totalSeatsStr, departureTimeDateStr,
            arrivalTimeDateStr;
    std::chrono::system_clock::time_point departureTime, arrivalTime;
    std::optional<std::chrono::system_clock::time_point> optTime;

    std::cout << "------ CREAZIONE VOLO ------\n";

    std::vector<const Airport *> airports = adminService.getAllAirports();

    if (airports.size() < 2) {
        std::cout << "Errore: devono esistere almeno 2 aeroporti\n";
        return;
    }

    clearScreen();
    printAllAirports(airports);

    std::cout << "Inserire dati nuovo Volo:\n";

    do {
        std::cout << "Id aeroporto di partenza: ";
        std::getline(std::cin, departureAirportIdStr);
        departureAirportId = stringToPositiveInteger(departureAirportIdStr);
        if (departureAirportId == -1)
            std::cout << "Errore: input non valido\n";
    } while (departureAirportId == -1);

    do {
        std::cout << "Orario di partenza (formato YYYY-MM-DD HH:MM): ";
        std::getline(std::cin, departureTimeDateStr);
        optTime = stringToTimePoint(departureTimeDateStr);
        if (optTime.has_value())
            departureTime = optTime.value();
        else
            std::cout << "Errore: input non valido\n";
    } while (!optTime.has_value());

    clearScreen();
    printAllAirports(airports);

    do {
        std::cout << "Id aeroporto di arrivo: ";
        std::getline(std::cin, arrivalAirportIdStr);
        arrivalAirportId = stringToPositiveInteger(arrivalAirportIdStr);
        if (arrivalAirportId == -1)
            std::cout << "Errore: input non valido\n";
    } while (arrivalAirportId == -1);

    do {
        std::cout << "Orario di arrivo (formato YYYY-MM-DD HH:MM): ";
        std::getline(std::cin, arrivalTimeDateStr);
        optTime = stringToTimePoint(arrivalTimeDateStr);
        if (optTime.has_value())
            arrivalTime = optTime.value();
        else
            std::cout << "Errore: input non valido\n";
    } while (!optTime.has_value());

    std::cout << std::endl;

    do {
        std::cout << "Posti totali: ";
        std::getline(std::cin, totalSeatsStr);
        totalSeats = stringToPositiveInteger(totalSeatsStr);
        if (totalSeats == -1)
            std::cout << "Errore: input non valido\n";
    } while (totalSeats == -1);

    do {
        std::cout << "Prezzo: ";
        std::getline(std::cin, priceStr);
        price = stringToPositiveInteger(priceStr);
        if (price == -1)
            std::cout << "Errore: input non valido\n";
    } while (price == -1);


    bool result = adminService.createFlight(departureAirportId, arrivalAirportId, departureTime, arrivalTime, price,
                                            totalSeats);

    std::cout << "---------------------------\n";

    if (result)
        std::cout << "Volo creato con successo!\n";
    else
        std::cout << "Errore: Impossibile creare il volo\n";

    waitInput();
}

void CLI::manageSingleFlight(const unsigned int id) {
    bool editing = true;
    while (editing) {
        clearScreen();
        const Flight *flight = adminService.getFlight(id);
        if (flight == nullptr) {
            std::cout << "Volo con id: " << id << " non trovato\n";
            return;
        }

        std::string departureAirportName = adminService.getAirport(flight->getDepartureAirportId())->getName();
        std::string arrivalAirportName = adminService.getAirport(flight->getArrivalAirportId())->getName();

        std::cout << "Volo selezionato:\n";

        std::cout << "ID:" << flight->getId() << "\t";
        std::cout << std::endl;
        std::cout << departureAirportName << " -> " << arrivalAirportName;
        std::cout << std::endl;
        std::cout << "Partenza: " << timePointToString(flight->getDepartureTime()) << "\t";
        std::cout << std::endl;
        std::cout << "Arrivo: " << timePointToString(flight->getArrivalTime()) << "\t";
        std::cout << std::endl;
        std::cout << "Prezzo: $" << flight->getPrice() << "\t";
        std::cout << "Posti totali: " << flight->getTotalSeats() << "\t";
        std::cout << "Posti occupati: " << flight->getBookedSeats() << "\t";
        std::cout << std::endl << std::endl;

        std::cout << "1 - Modifica Aeroporto di partenza\n";
        std::cout << "2 - Modifica Aeroporto di arrivo\n";
        std::cout << "3 - Modifica data e ora di partenza\n";
        std::cout << "4 - Modifica data e ora di arrivo\n";
        std::cout << "5 - Modifica prezzo\n";
        std::cout << "6 - Modifica posti totali\n";
        std::cout << "7 - Elimina\n";
        std::cout << "0 - Indietro\n";

        char subChoice;
        std::cin >> subChoice;
        std::string userInput;
        std::cin.ignore();
        switch (subChoice) {
            case '1': {
                std::string formattedIata;
                do {
                    std::cout << "Inserisci nuovo id aeroporto di partenza: ";
                    std::getline(std::cin, userInput);
                    std::cout << std::endl;
                    formattedIata = iataFormat(userInput);
                    if (formattedIata == "")
                        std::cout << "Il codice IATA deve avere esattemente 3 caratteri!\n";
                } while (formattedIata == "");
                //adminService.modifyAirportIATA(airport->getId(), formattedIata);
                break;
            }
            case '2':
                std::cout << "Inserisci nuova Nazione: ";
                std::getline(std::cin, userInput);
                std::cout << std::endl;
                //adminService.modifyAirportNation(airport->getId(), userInput);
                break;
            case '3':
                std::cout << "Inserisci nuova Città: ";
                std::getline(std::cin, userInput);
                std::cout << std::endl;
                //adminService.modifyAirportCity(airport->getId(), userInput);
                break;
            case '4':
                std::cout << "Inserisci nuovo Nome: ";
                std::getline(std::cin, userInput);
                std::cout << std::endl;
                //adminService.modifyAirportName(airport->getId(), userInput);
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
                waitInput();
                break;
        }
    }
}

void CLI::adminAirportsMenu() {
    std::string choice;
    while (true) {
        std::string strChoice;
        clearScreen();
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
            if (id == -1)
                continue;
            manageSingleAirport(id);
        }
    }
}

void CLI::adminFlightsMenu() {
    std::string choice;
    while (true) {
        clearScreen();
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
                waitInput();
                continue;
            }

            manageSingleFlight(id);
        }
    }
}

void CLI::loginMenu() {
    bool running = true;
    while (running) {
        userStruct = {};
        clearScreen();
        std::string strChoice;
        std::cout << "Benvenuto su Ciab Booking Service\n\n";
        std::cout << "1 - Accedi\n";
        std::cout << "2 - Registrati\n\n";
        std::cout << "0 - Esci\n";
        std::cin >> strChoice;
        int choice = stringToPositiveInteger(strChoice);
        if (choice == -1)
            continue;

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
                continue;
        }

        if (running == false)
            break;

        if (userStruct.responseCode != AuthResponse::OK)
            continue;
        if (userStruct.role == UserRole::Customer)
            customerMenu();
        else if (userStruct.role == UserRole::Admin)
            adminMenu();
    }
    authService.close();
    adminService.close();
    customerService.close();
}

UserStruct CLI::login() const {
    clearScreen();
    std::cout << "---------- Login ----------\n";
    std::string email, password;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "---------------------------\n";

    UserStruct result = authService.login(email, password);
    switch (result.responseCode) {
        case AuthResponse::OK:
            std::cout << "Benvenuto!\n";
            break;
        case AuthResponse::WRONG_PASSWORD:
        case AuthResponse::WRONG_EMAIL:
            std::cout << "Errore: combinazione email/password errata\n";
            break;
    }
    waitInput();
    return result;
}

//todo (non qui) wait a customer quando stampa il menu

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

UserStruct CLI::signIn() const {
    clearScreen();
    std::cout << "------ Registrazione ------\n";
    std::string name, email, password;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "---------------------------\n";
    UserStruct result = authService.signIn(name, email, password);
    switch (result.responseCode) {
        case AuthResponse::OK:
            std::cout << "Benvenuto!\n";
            break;
        case AuthResponse::WRONG_PASSWORD:
        case AuthResponse::WRONG_EMAIL:
            std::cout << "Errore: esiste già un utente con quella email\n";
            break;
    }
    waitInput();
    return result;
}
