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
    flightRepo(flightRepo),
    reservationRepo(reservationRepo),
    airportRepo(airportRepo),
    userRepo(userRepo){};

    bool book(unsigned int userId, unsigned int flightId, unsigned int ticketsNumber) const;

    std::vector<const Flight *> getAllFlights() const;
    const Flight* getFlight(unsigned int flightId) const;
    const Airport* getAirport(unsigned int airportId) const;
    const Reservation* getReservation(unsigned int reservationId) const;
    std::vector<const Reservation*> getAllReservations() const;
    void changeUserName(unsigned int userId, const std::string &newName) const;
    void changeUserEmail(unsigned int userId, const std::string &newEmail) const;
    const User* getUser(unsigned int userId) const;

    void close() const;
};


#endif //CUSTOMERSERVICE_H
