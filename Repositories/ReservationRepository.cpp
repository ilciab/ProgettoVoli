//
// Created by ilciab on 12/4/25.
//

#include "ReservationRepository.h"

#include <chrono>
#include <fstream>

#include "../Utils/RepositoryUtils.h"

Reservation * ReservationRepository::getById_internal(unsigned id) {
    for (const auto &reservation : reservations) {
        if (reservation->getId() == id) {
            return reservation.get();
        }
    }
    return nullptr;
}

const Reservation * ReservationRepository::getById(unsigned id) const {
    for (const auto &reservation : reservations) {
        if (reservation->getId() == id) {
            return reservation.get();
        }
    }
    return nullptr;
}

unsigned int ReservationRepository::createReservation(const unsigned int ownerUserId, const unsigned int flightId) {
    unsigned int id = idGen.getNextId();
    reservations.emplace_back(std::make_unique<Reservation>(id, ownerUserId, flightId ));
    return id;
}

void ReservationRepository::remove(unsigned id) {
    removeById(reservations, id);
}

void ReservationRepository::write() {
    std::fstream file = openFile(path, std::ios::out | std::ios::binary | std::ios::trunc);

    for (const auto &reservation: reservations) {
        unsigned int id = reservation->getId();
        unsigned int ownerUserId = reservation->getOwnerUserId();
        unsigned int flightId = reservation->getFlightId();
        file.write(reinterpret_cast<const char *>(&id), sizeof(id));
        file.write(reinterpret_cast<const char *>(&ownerUserId), sizeof(ownerUserId));
        file.write(reinterpret_cast<const char *>(&flightId), sizeof(flightId));
    }
    file.close();
}

void ReservationRepository::load() {
    std::fstream file = openFile(path, std::ios::in | std::ios::binary);
    unsigned int largestId = 0;
    while (true) {
        unsigned int id;
        unsigned int ownerUserId;
        unsigned int flightId;

        file.read(reinterpret_cast<char *>(&id), sizeof(id));
        file.read(reinterpret_cast<char *>(&ownerUserId), sizeof(ownerUserId));
        file.read(reinterpret_cast<char *>(&flightId), sizeof(flightId));

        if (file.fail())
            break;
        reservations.emplace_back(std::make_unique<Reservation>(id, ownerUserId, flightId));
        largestId = std::max(largestId, id);
    }
    idGen.setStartingId(largestId);
    file.close();
}

std::vector<const Reservation *> ReservationRepository::getAll() {
    std::vector<const Reservation *> allReservations;
    for (const auto &reservaton: reservations) {
        allReservations.push_back(reservaton.get());
    }
    return allReservations;
}


