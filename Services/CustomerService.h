//
// Created by ciabu on 03/12/2025.
//

#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H


#include "../Repositories/AirportRepository.h"
#include "../Repositories/FlightRepository.h"
#include "../Repositories/UserRepository.h"
#include "../Repositories/ReservationRepository.h"

class CustomerService {
private:
    FlightRepository &flightRepo;
    ReservationRepository &reservationRepo;
    AirportRepository &airportRepo;
    UserRepository &userRepo;

public:
    explicit CustomerService(AirportRepository &airportRepo, FlightRepository &flightRepo, ReservationRepository &reservationRepo, UserRepository &userRepo) :
    airportRepo(airportRepo),
    flightRepo(flightRepo),
    reservationRepo(reservationRepo),
    userRepo(userRepo){};

    bool book(unsigned int userId, unsigned int flightId, unsigned int ticketsNumber) const;

    std::vector<const Flight *> getAllFlights();
    const Flight* getFlight(unsigned int flightId) const;
    const Airport* getAirport(unsigned int airportId) const;
    const Reservation* getReservation(unsigned int reservationId) const;
    std::vector<const Reservation*> getAllReservations() const;
    bool changeUserPassword(unsigned int userId, const std::string &oldPassword, const std::string &newPassword) const;
    const User* getUser(unsigned int userId) const;

    static std::string hashPassword(const std::string &password) {
        uint64_t h = 5381;
        for (unsigned char c: password)
            h = (h * 33) + c;
        return std::to_string(h);
    }

    void close() const;
};


#endif //CUSTOMERSERVICE_H
