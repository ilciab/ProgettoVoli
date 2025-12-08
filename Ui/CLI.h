//
// Created by ciabu on 24/09/2025.
//

#ifndef CLI_H
#define CLI_H
#include "../Services/AuthService.h"
#include "../Domain/UserStruct.h"
#include "../Services/AdminService.h"
#include "../Services/CustomerService.h"


class CLI {

    private:
        std::optional<UserStruct> userStruct;
        AuthService& authService;
        AdminService& adminService;
        CustomerService& customerService;


    public:
        CLI(AuthService &authService, AdminService &adminService, CustomerService &customerService)
            : authService(authService),
              adminService(adminService),
              customerService(customerService) {
        }


        std::string timepointToString(std::chrono::system_clock::time_point tp) const;

        void clearScreen() const;
        void waitInput() const;
        void adminMenu();
        void adminUsersMenu();
        void printAllUsers(const std::vector<const User*> &users) const;
        void printAllAirports(const std::vector<const Airport*> &airports) const;
        void printAllFlights(const std::vector<const Flight*> &flights) const;
        void printAllUserReservations(const std::vector<const Reservation*> &reservations, unsigned int userId) const;


        void adminAirportsMenu();
        void createAirportWizard();
        void manageSingleAirport(unsigned int id);

        void adminFlightsMenu();
        void createFlightWizard();
        void manageSingleFlight(unsigned int id);

        void adminBookingsMenu();
        void customerMenu();
        void customerProfileMenu();
        void customerBookingsMenu();
        void loginMenu();



        std::optional<UserStruct> signIn();
        std::optional<UserStruct> login();

        std::string iataFormat(std::string iata);

};


#endif //CLI_H
