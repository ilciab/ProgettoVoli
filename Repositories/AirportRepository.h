//
// Created by ilciab on 11/16/25.
//

#ifndef PROGETTOVOLI_AIRPORTREPOSITORY_H
#define PROGETTOVOLI_AIRPORTREPOSITORY_H
#include <memory>

#include "RepositoryInterface.h"
#include "../Domain/Airport.h"


class AirportRepository : public RepositoryInterface<Airport>{
    std::vector<std::unique_ptr<Airport>> airports;
    std::string path;
    IdGenerator idGen;

public:
    explicit AirportRepository(const std::string &path)
        : path(path) {
        AirportRepository::load();
    }

    void remove(unsigned int id) override;
    void write() override;
    void load() override;

    const Airport* getById(unsigned int id) const override;
    Airport *getById_internal(unsigned int id) override;
    const Airport* getByIata(std::string iata) const;
    std::vector<const Airport *> getAll() override;

    unsigned int createAirport(const std::string &iata, const std::string &nation, const std::string &city, const std::string &name);

    void setAirportIata(unsigned int airportId, const std::string &newIata);
    void setAirportNation(unsigned int airportId, const std::string &newNation);
    void setAirportName(unsigned int airportId, const std::string &newName);
    void setAirportCity(unsigned int airportId, const std::string &newCity);


};


#endif //PROGETTOVOLI_AIRPORTREPOSITORY_H