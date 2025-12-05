//
// Created by ilciab on 12/4/25.
//

#ifndef PROGETTOVOLI_RESERVATIONREPOSITORY_H
#define PROGETTOVOLI_RESERVATIONREPOSITORY_H
#include <memory>

#include "RepositoryInterface.h"
#include "../Domain/Reservation.h"


class ReservationRepository : public RepositoryInterface<Reservation>{

    Reservation * getById_internal(unsigned id) override;
    std::vector<std::unique_ptr<Reservation>> reservations;
    std::string path;
    IdGenerator idGen;

public:

    explicit ReservationRepository(const std::string &path) : path(path) {
        load();
    };


    const Reservation * getById(unsigned id) const override;
    unsigned int createReservation(const unsigned int ownerUserId, const unsigned int flightId);

    void remove(unsigned id) override;

    void write() override;

    void load() override;

    std::vector<const Reservation *> getAll() override;
};


#endif //PROGETTOVOLI_RESERVATIONREPOSITORY_H