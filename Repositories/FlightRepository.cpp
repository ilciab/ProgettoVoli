//
// Created by ilciab on 11/20/25.
//

#include "FlightRepository.h"

#include <fstream>
#include <iostream>

#include "../Utils/RepositoryUtils.h"

Flight *FlightRepository::getById_internal(const unsigned int id) {
    for (const auto &flight: flights) {
        if (flight->getId() == id) {
            return flight.get();
        }
    }
    return nullptr;
}

const Flight *FlightRepository::getById(const unsigned int id) const {
    for (const auto &flight: flights) {
        if (flight->getId() == id) {
            return flight.get();
        }
    }
    return nullptr;
}

void FlightRepository::remove(const unsigned int id) {
    removeById(flights, id);
}

void FlightRepository::write() {
    std::fstream file = openFile(path, std::ios::out | std::ios::binary | std::ios::trunc);

    for (const auto &flight: flights) {
        unsigned int id = flight->getId();
        unsigned int departureAirportId = flight->getDepartureAirportId();
        unsigned int arrivalAirportId = flight->getArrivalAirportId();
        unsigned int bookedSeats = flight->getBookedSeats();
        unsigned int totalSeats = flight->getTotalSeats();
        auto departureTime = flight->getDepartureTime().time_since_epoch();
        auto arrivalTime = flight->getArrivalTime().time_since_epoch();
        long long departureSeconds = std::chrono::duration_cast<std::chrono::seconds>(departureTime).count();
        long long arrivalSeconds = std::chrono::duration_cast<std::chrono::seconds>(arrivalTime).count();
        float price = flight->getPrice();
        file.write(reinterpret_cast<const char *>(&id), sizeof(id));
        file.write(reinterpret_cast<const char *>(&departureAirportId), sizeof(departureAirportId));
        file.write(reinterpret_cast<const char *>(&arrivalAirportId), sizeof(arrivalAirportId));
        file.write(reinterpret_cast<const char *>(&departureSeconds), sizeof(departureSeconds));
        file.write(reinterpret_cast<const char *>(&arrivalSeconds), sizeof(arrivalSeconds));
        file.write(reinterpret_cast<const char *>(&bookedSeats), sizeof(bookedSeats));
        file.write(reinterpret_cast<const char *>(&totalSeats), sizeof(totalSeats));
        file.write(reinterpret_cast<const char *>(&price), sizeof(price));
    }
    file.close();
}

void FlightRepository::load() {
    std::fstream file = openFile(path, std::ios::in | std::ios::binary);
    unsigned int largestId;
    while (true) {
        unsigned int id;
        unsigned int departureAirportId;
        unsigned int arrivalAirportId;
        unsigned int bookedSeats;
        unsigned int totalSeats;
        long long departureSeconds;
        long long arrivalSeconds;
        float price;

        file.read(reinterpret_cast<char *>(&id), sizeof(id));
        file.read(reinterpret_cast<char *>(&departureAirportId), sizeof(departureAirportId));
        file.read(reinterpret_cast<char *>(&arrivalAirportId), sizeof(arrivalAirportId));
        file.read(reinterpret_cast<char *>(&departureSeconds), sizeof(departureSeconds));
        file.read(reinterpret_cast<char *>(&arrivalSeconds), sizeof(arrivalSeconds));
        file.read(reinterpret_cast<char *>(&bookedSeats), sizeof(bookedSeats));
        file.read(reinterpret_cast<char *>(&totalSeats), sizeof(totalSeats));
        file.read(reinterpret_cast<char *>(&price), sizeof(price));

        auto departureTime = std::chrono::system_clock::time_point(std::chrono::seconds(departureSeconds));
        auto arrivalTime = std::chrono::system_clock::time_point(std::chrono::seconds(arrivalSeconds));
        if (file.fail())
            break;

        flights.emplace_back(std::make_unique<Flight>(id, departureAirportId, arrivalAirportId, departureTime,
                                                      arrivalTime, price, totalSeats, bookedSeats));

        largestId = std::max(largestId, id);
    }
    idGen.setStartingId(largestId);
    file.close();
}

std::vector<const Flight *> FlightRepository::getAll() {
    std::vector<const Flight *> flights;
    for (const auto &flight: flights) {
        flights.push_back(flight);
    }
    return flights;
}

void FlightRepository::setFlightDepartureAirport(unsigned int flightId, unsigned int departureAirportId) {
    getById_internal(flightId)->setDepartureAirportId(departureAirportId);
}

void FlightRepository::setFlightArrivalAirport(unsigned int flightId, unsigned int arrivalAirportId) {
    getById_internal(flightId)->setArrivalAirportId(arrivalAirportId);
}

void FlightRepository::setFlightDepartureTime(unsigned int flightId, std::chrono::system_clock::time_point departureTime) {
    getById_internal(flightId)->setDepartureTime(departureTime);
}

void FlightRepository::setFlightArrivalTime(unsigned int flightId, std::chrono::system_clock::time_point arrivalTime) {
    getById_internal(flightId)->setArrivalTime(arrivalTime);
}

void FlightRepository::setFlightPrice(unsigned int flightId, float price) {
    getById_internal(flightId)->setPrice(price);
}

void FlightRepository::setFlightTotalSeats(unsigned int flightId, unsigned int totalSeats) {
    getById_internal(flightId)->setTotalSeats(totalSeats);
}

unsigned int FlightRepository::createFlight(const unsigned int departureAirportId, const unsigned int arrivalAirportId,
    const std::chrono::system_clock::time_point &departureTime, const std::chrono::system_clock::time_point &arrivalTime, const float price,
    const unsigned int totalSeats) {
    unsigned int id = idGen.getNextId();
    flights.emplace_back(std::make_unique<Flight>(id, departureAirportId, arrivalAirportId,
        departureTime, arrivalTime, price, totalSeats));
    return id;
}
