//
// Created by ciabu on 03/12/2025.
//

#include "CustomerService.h";

void CustomerService::book(unsigned int userId, unsigned int flightId, unsigned int ticketsNumber) const {
    for (int i = 0; i<=ticketsNumber; i++)
        reservationRepo.createReservation(userId,flightId);
}

std::vector<const Reservation *> CustomerService::getAllReservations() const {
    return reservationRepo.getAll();
}

void CustomerService::close() {
    reservationRepo.write();
}
