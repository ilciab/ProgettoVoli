//
// Created by ciabu on 24/09/2025.
//

#ifndef CLI_H
#define CLI_H
#include "../Services/AuthService.h"
#include "../Domain/UserStruct.h"
#include "../Services/AdminService.h"


class CLI {

    private:
        std::optional<UserStruct> userStruct;
        AuthService& authService;
        AdminService& adminService;


    public:
        CLI(AuthService &auth_service, AdminService &admin_service)
            : authService(auth_service),
              adminService(admin_service) {
        }


        std::string &timepointToString(std::chrono::system_clock::time_point tp);

        void adminMenu();
        void adminUsersMenu();
        void printAllUsers(const std::vector<const User*> &users) const;
        void printAllAirports(const std::vector<const Airport*> &airports) const;
        void printAllFlights(const std::vector<const Flight*> &flights) const;




        void adminAirportsMenu();
        void createAirportWizard();
        void manageSingleAirport(const unsigned int id);

        void adminFlightsMenu();
        void createFlightWizard();
        void manageSingleFlight(const unsigned int id);

        void adminBookingsMenu();
        void customerMenu();
        void customerProfileMenu();
        void customerAirportsMenu();
        void customerFlightsMenu();
        void customerBookingsMenu();
        void loginMenu();



        std::optional<UserStruct> signIn();
        std::optional<UserStruct> login();

        std::string iataFormat(std::string iata);


};



#endif //CLI_H
