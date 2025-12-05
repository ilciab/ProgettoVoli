//
// Created by ciabu on 03/12/2025.
//

#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H


#include "../Repositories/FlightRepository.h"
#include "../Repositories/ReservationRepository.h"

class CustomerService {
private:
    FlightRepository &flightRepo;
    ReservationRepository &reservationRepo;

public:
    explicit CustomerService(FlightRepository &flightRepo, ReservationRepository &reservationRepo) :
    flightRepo(flightRepo),
    reservationRepo(reservationRepo) {};

    void book(unsigned int userId, unsigned int flightId, unsigned int ticketsNumber) const;

    std::vector<const Reservation*> getAllReservations() const;


    void close();
};


#endif //CUSTOMERSERVICE_H
