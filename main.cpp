#include <iostream>

#include "domain/Airport.h"
#include "repo/AirportRepository.h"
#include "ui/CLI.h"
#include "service/AuthService.h"
using namespace std;


int main() {
    UserRepository userRepo(std::string("users.txt"), std::string("admins.txt"));
    AirportRepository airportRepo(std::string("airports.txt"));
    AuthService authService(userRepo);
    AdminService adminService(userRepo, airportRepo);
    CLI cli(authService, adminService);
    cli.loginMenu();
    return 0;
}
