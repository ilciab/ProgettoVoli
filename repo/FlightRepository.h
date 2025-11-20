//
// Created by ilciab on 11/20/25.
//

#ifndef PROGETTOVOLI_FLIGHTREPOSITORY_H
#define PROGETTOVOLI_FLIGHTREPOSITORY_H
#include "RepositoryInterface.h"
#include "../domain/Flight.h"


class FlightRepository : public RepositoryInterface<Flight>{

std::vector<std::unique_ptr<Flight>> flights;
Flight * getById_internal(int id) override;
IdGenerator idGen;

public:

    const Flight * getById(int id) const override;
    void remove(int id) override;
    void write() override;
    void load() override;
    std::vector<const Flight *> getAll() override;
};


#endif //PROGETTOVOLI_FLIGHTREPOSITORY_H