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
    IdGenerator idGen;

public:
    AirportRepository(const std::string &path)
        : path(path) {
        AirportRepository::load();
    }

    void remove(int id) override;
    void write() override;
    void load() override;

    const Airport* getById(unsigned int id) const override;
    Airport *getById_internal(int id) override;
    std::vector<const Airport *> getAll() override;

    void setAirportIata(unsigned int airportId, const std::string &newIata);
    void setAirportNation(unsigned int airportId, const std::string &newNation);
    void setAirportName(unsigned int airportId, const std::string &newName);
    void setAirportCity(unsigned int airportId, const std::string &newCity);
};


#endif //PROGETTOVOLI_AIRPORTREPOSITORY_H