//
// Created by ilciab on 11/16/25.
//

#include "AirportRepository.h"

#include <fstream>
#include <iostream>
#include <ranges>

#include "../util/RepositoryUtils.h"


void AirportRepository::remove(int id) {
    removeById(airports, id);
}




void AirportRepository::write() {
    std::fstream file = openFile(path, std::ios::out | std::ios::binary | std::ios::trunc);

    for (const auto &airport: airports) {
        unsigned int id = airport->getId();
        file.write(reinterpret_cast<const char *>(&id), sizeof(id));
        writeBinaryString(file, airport->getIata());
        writeBinaryString(file, airport->getNation());
        writeBinaryString(file, airport->getCity());
        writeBinaryString(file, airport->getName());
    }
    file.close();
}


void AirportRepository::load() {
    std::fstream file = openFile(path, std::ios::in | std::ios::binary);
    while (true) {
        unsigned int id;
        file.read(reinterpret_cast<char *>(&id), sizeof(id));
        if (file.fail())
            break;
        std::string name = readBinaryString(file);
        std::string nation = readBinaryString(file);
        std::string city = readBinaryString(file);
        std::string iata = readBinaryString(file);

        airports.emplace_back(std::make_unique<Airport>(id, name, nation, city, iata));
    }
}


std::vector<const Airport *> AirportRepository::getAll() {
    std::vector<const Airport *> allAirports;
    for (const auto &airport: airports) {
        allAirports.push_back(airport.get());
    }
    return allAirports;
}

const Airport *AirportRepository::getById(unsigned int id) const {
    return nullptr;
}

Airport *AirportRepository::getById_internal(int id) {
    return nullptr;
}


void AirportRepository::setAirportIata(unsigned int airportId, const std::string &newIata) {
    getById_internal(airportId)->setIata(newIata);
}

void AirportRepository::setAirportNation(unsigned int airportId, const std::string &newNation) {
    getById_internal(airportId)->setNation(newNation);
}

void AirportRepository::setAirportName(unsigned int airportId, const std::string &newName) {
    getById_internal(airportId)->setName(newName);
}

void AirportRepository::setAirportCity(unsigned int airportId, const std::string &newCity) {
    getById_internal(airportId)->setCity(newCity);
}
