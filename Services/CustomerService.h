//
// Created by ciabu on 03/12/2025.
//

#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H


#include "../Repositories/AirportRepository.h"
#include "../Repositories/FlightRepository.h"
#include "../Repositories/ReservationRepository.h"

class CustomerService {
private:
    FlightRepository &flightRepo;
    ReservationRepository &reservationRepo;
    AirportRepository &airportRepo;

public:
    explicit CustomerService(AirportRepository &airportRepo, FlightRepository &flightRepo, ReservationRepository &reservationRepo) :
    airportRepo(airportRepo),
    flightRepo(flightRepo),
    reservationRepo(reservationRepo) {};

    bool book(unsigned int userId, unsigned int flightId, unsigned int ticketsNumber) const;

    std::vector<const Flight *> getAllFlights();
    const Flight* getFlight(unsigned int flightId) const;
    const Airport* getAirport(unsigned int airportId) const;
    const Reservation* getReservation(unsigned int reservationId) const;
    std::vector<const Reservation*> getAllReservations() const;

    void close() const;
};


#endif //CUSTOMERSERVICE_H
