//
// Created by ilciab on 11/16/25.
//

#ifndef PROGETTOVOLI_AIRPORTREPOSITORY_H
#define PROGETTOVOLI_AIRPORTREPOSITORY_H
#include <memory>

#include "RepositoryInterface.h"
#include "../domain/Airport.h"


class AirportRepository : public RepositoryInterface<Airport>{
    std::vector<std::unique_ptr<Airport>> airports;
    std::string path;

public:
    AirportRepository(const std::string &path)
        : path(path) {
        AirportRepository::load();
    }

private:
    IdGenerator idGen;

public:

    void remove(int id) override;
    void add(const Airport &) override;
    void write() override;
    void load() override;
    const Airport* getById(int id) const override;
    Airport *getById_internal(int id) override;
    const std::vector<const Airport*> getAll() override;


};


#endif //PROGETTOVOLI_AIRPORTREPOSITORY_H