//
// Created by ilciab on 11/16/25.
//

#include "AirportRepository.h"

#include <fstream>
#include <iostream>
#include <ranges>

#include "../Utils/RepositoryUtils.h"


void AirportRepository::remove(const unsigned int id) {
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
    unsigned int largestId = 0;
    std::fstream file = openFile(path, std::ios::in | std::ios::binary);
    while (true) {
        unsigned int id;
        file.read(reinterpret_cast<char *>(&id), sizeof(id));
        if (file.fail())
            break;
        std::string iata = readBinaryString(file);
        std::string nation = readBinaryString(file);
        std::string city = readBinaryString(file);
        std::string name = readBinaryString(file);
        airports.emplace_back(std::make_unique<Airport>(id, iata, nation, city, name));
        largestId = std::max(largestId, id);
    }
    idGen.setStartingId(largestId);
    file.close();
}


std::vector<const Airport *> AirportRepository::getAll() {
    std::vector<const Airport *> allAirports;
    for (const auto &airport: airports) {
        allAirports.push_back(airport.get());
    }
    return allAirports;
}

unsigned int AirportRepository::createAirport(const std::string &iata, const std::string &nation,
    const std::string &city, const std::string &name) {
    unsigned int id = idGen.getNextId();
    airports.emplace_back(std::make_unique<Airport>(id, iata, nation, city, name));
    return id;
}

const Airport *AirportRepository::getById(const unsigned int id) const {
    for (const auto &airport: airports) {
        if (airport->getId() == id)
            return airport.get();
    }
    return nullptr;
}

Airport *AirportRepository::getById_internal(const unsigned int id) {
    for (const auto &airport: airports) {
        if (airport->getId() == id)
            return airport.get();
    }
    return nullptr;
}

const Airport * AirportRepository::getByIata(std::string iata) const {
    for (const auto &airport: airports) {
        if (airport->getIata() == iata)
            return airport.get();
    }
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
