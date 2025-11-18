//
// Created by ciabu on 24/09/2025.
//

#ifndef CLI_H
#define CLI_H
#include "../service/AuthService.h"
#include "../domain/UserStruct.h"
#include "../service/AdminService.h"


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

        void adminMenu();

        void printAllUsers();

        void adminUsersMenu();

        void printAllAirports();

        void adminAirportsMenu();
        void adminFlightsMenu();
        void adminBookingsMenu();
        void customerMenu();
        void customerProfileMenu();
        void customerAirportsMenu();
        void customerFlightsMenu();
        void customerBookingsMenu();
        void loginMenu();

        std::optional<UserStruct> signIn();

        std::optional<UserStruct> login();
};



#endif //CLI_H
