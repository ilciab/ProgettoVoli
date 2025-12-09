//
// Created by ciabu on 03/12/2025.
//

#include "CustomerService.h"
//mettere un responseCode
bool CustomerService::book(const unsigned int userId, const unsigned int flightId, const unsigned int ticketsNumber) const {
    const Flight* flight = getFlight(flightId);
    unsigned int freeSeats = flight->getTotalSeats() - flight->getBookedSeats();
    if(freeSeats<ticketsNumber)
        return false;

    for (int i = 0; i<=ticketsNumber; i++){
        reservationRepo.createReservation(userId,flightId);
    }

    

    return true;
}

const Flight * CustomerService::getFlight(const unsigned int flightId) const {
    return flightRepo.getById(flightId);
}

const Airport * CustomerService::getAirport(const unsigned int airportId) const {
    return airportRepo.getById(airportId);
}

const Reservation * CustomerService::getReservation(const unsigned int reservationId) const {
    return reservationRepo.getById(reservationId);
}

std::vector<const Flight *> CustomerService::getAllFlights() {
    return flightRepo.getAll();
}

std::vector<const Reservation *> CustomerService::getAllReservations() const {
    return reservationRepo.getAll();
}

void CustomerService::close() const {
    reservationRepo.write();
}
