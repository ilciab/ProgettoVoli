#include "Repositories/AirportRepository.h"
#include "Repositories/FlightRepository.h"
#include "Repositories/ReservationRepository.h"
#include "Ui/CLI.h"
#include "Services/AuthService.h"

int main() {
    UserRepository userRepo(std::string("users.txt"), std::string("admins.txt"));
    AirportRepository airportRepo(std::string("airports"));
    FlightRepository flightRepo(std::string("flights"));
    ReservationRepository reservationRepo(std::string("reservations"));
    AuthService authService(userRepo);
    AdminService adminService(userRepo, airportRepo, flightRepo);
    CustomerService customerService(airportRepo, flightRepo, reservationRepo, userRepo);
    CLI cli(authService, adminService, customerService);
    cli.loginMenu();
    return 0;
}
