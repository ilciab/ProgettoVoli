//
// Created by ilciab on 11/16/25.
//

#include "AirportRepository.h"

#include <fstream>
#include <iostream>
#include <ranges>


void AirportRepository::remove(int id) {
}

void AirportRepository::add(const Airport &) {
}

void writeBinaryString(std::fstream &file, const std::string &str) {
    size_t length = str.length();
    file.write(reinterpret_cast<const char *>(&length), sizeof(length));
    file.write(str.data(), length);
}


void AirportRepository::write() {
    auto airportPtr = std::make_unique<Airport>(1, "suca", "suca", "suca", "suca");
    airports.push_back(std::move(airportPtr));
    // 1. Apri il file
    std::fstream file(path, std::ios::out | std::ios::binary);

    if (!file) {
        std::cout << "Errore: Impossibile aprire il file binario in scrittura." << std::endl;
        return;
    }

    // 2. Cicla su tutti gli aeroporti
    for (const auto &airport: airports) {
        // 1. SALVA l'ID in una variabile locale
        unsigned int id = airport->getId();
        // 'id' ora esiste in memoria e ha un indirizzo stabile

        // 2. SCRIVI usando l'indirizzo della variabile locale
        file.write(reinterpret_cast<const char *>(&id), sizeof(id));


        // (Aggiungi qui altri membri fissi, es. 'double price', 'int seats' se li avessi)

        // 3b. Scrivi i membri a dimensione VARIABILE (usando l'helper)
        writeBinaryString(file, airport->getCity());
        writeBinaryString(file, airport->getNation());
        writeBinaryString(file, airport->getCity());
        writeBinaryString(file, airport->getIata());
    }

    file.close();
}




std::string readBinaryString(std::fstream &file) {
    size_t length = 0;

    file.read(reinterpret_cast<char *>(&length), sizeof(length));

    if (file.fail())
        return "";

    std::string str(length, '\0');
    file.read(&str[0], length);

    return str;
}


void AirportRepository::load() {
    std::fstream file(path, std::ios::in | std::ios::binary);

    if (!file)
        return;
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


const std::vector<const Airport *> AirportRepository::getAll() {
    std::vector<const Airport *> allAirports;
    return allAirports;
}

const Airport *AirportRepository::getById(int id) const {
    return nullptr;
}

Airport * AirportRepository::getById_internal(int id) {
    return nullptr;
}






