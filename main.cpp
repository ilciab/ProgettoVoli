#include <iostream> 
#include "Domain/Airport.h"
#include "Repositories/AirportRepository.h"
#include "Repositories/FlightRepository.h"
#include "Ui/CLI.h"
#include "Services/AuthService.h"

int main() {
    UserRepository userRepo(std::string("users.txt"), std::string("admins.txt"));
    AirportRepository airportRepo(std::string("airports"));
    FlightRepository flightRepo(std::string("flights"));
    AuthService authService(userRepo);
    AdminService adminService(userRepo, airportRepo, flightRepo);
    CLI cli(authService, adminService);
    cli.loginMenu();
    return 0;
}
