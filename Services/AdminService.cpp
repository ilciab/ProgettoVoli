//
// Created by ciabu on 30/09/2025.
//

#include "AdminService.h"

#include <iostream>

std::vector<const User *> AdminService::getAllUsers() const { return userRepo.getAll(); }
const User *AdminService::getUser(const unsigned int userId) const { return userRepo.getById(userId); }

void AdminService::modifyUserName(const unsigned int userId, const std::string &newName) const { userRepo.setUserName(userId, newName);}
void AdminService::modifyUserEmail(const unsigned int userId, const std::string &newEmail) const { userRepo.setUserEmail(userId, newEmail); }

void AdminService::deleteUser(const unsigned int userId) const { userRepo.remove(userId); }


bool AdminService::createAirport(const std::string& iata, const std::string& nation, const std::string& city, const std::string& name) const {
    if (airportRepo.getByIata(iata) != nullptr)
        return false;
    airportRepo.createAirport(iata, nation, city, name);
    return true;
}
std::vector<const Airport *> AdminService::getAllAirports() const { return airportRepo.getAll(); }
const Airport *AdminService::getAirport(const unsigned int airportId) const { return airportRepo.getById(airportId); }

void AdminService::modifyAirportName(const unsigned int airportId, const std::string &newName) const { airportRepo.setAirportName(airportId, newName); }
void AdminService::modifyAirportNation(const unsigned int airportId, const std::string &newNation) const { airportRepo.setAirportNation(airportId, newNation); }
void AdminService::modifyAirportCity(const unsigned int airportId, const std::string &newCity) const { airportRepo.setAirportCity(airportId, newCity); }
void AdminService::modifyAirportIATA(const unsigned int airportId, const std::string &newIata) const { airportRepo.setAirportIata(airportId, newIata); }

void AdminService::deleteAirport(const unsigned int airportId) const { airportRepo.remove(airportId); }

bool AdminService::createFlight(const unsigned int departureAirportId, const unsigned int arrivalAirportId,
                                const std::chrono::system_clock::time_point &departureTime, const std::chrono::system_clock::time_point &arrivalTime, const float price, const unsigned int totalSeats) const {

    if(arrivalTime<=departureTime){
        std::cerr<<"Orario arrivo minore partenza\n";
        return false;
    }

    if(departureAirportId == arrivalAirportId){
        std::cerr<<"Id partenza e arrivo uguale\n";
        return false;
    }

    if(airportRepo.getById(departureAirportId) == nullptr or airportRepo.getById(arrivalAirportId) == nullptr){
        std::cerr<<"Id inesistente\n";
        return false;
    }

    flightRepo.createFlight(departureAirportId, arrivalAirportId, departureTime, arrivalTime, price, totalSeats);
    airportRepo.increaseUsages(departureAirportId);
    airportRepo.increaseUsages(arrivalAirportId);
    return true;
}


std::vector<const Flight *> AdminService::getAllFlights() const { return flightRepo.getAll(); }
const Flight * AdminService::getFlight(const unsigned int flightId) const { return flightRepo.getById(flightId); }

bool AdminService::modifyFlightDepartureAirportId(const unsigned int flightId, const unsigned int newDepartureAirportId) const {
    if (airportRepo.getById(newDepartureAirportId) == nullptr)
        return false;
    flightRepo.setFlightDepartureAirport(flightId, newDepartureAirportId);
    return true;
}

bool AdminService::modifyFlightArrivalAirportId(const unsigned int flightId, const unsigned int newArrivalAirportId) const {
    if (airportRepo.getById(newArrivalAirportId) == nullptr)
        return false;
    flightRepo.setFlightArrivalAirport(flightId, newArrivalAirportId);
    return true;
}

void AdminService::modifyFlightDepartureTime(const unsigned int flightId, const std::chrono::system_clock::time_point &newDepartureTime) const {
    flightRepo.setFlightDepartureTime(flightId, newDepartureTime);
}

void AdminService::modifyFlightArrivalTime(const unsigned int flightId, const std::chrono::system_clock::time_point &newArrivalTime) const {
    flightRepo.setFlightArrivalTime(flightId, newArrivalTime);
}

void AdminService::modifyFlightPrice(const unsigned int flightId, const float newPrice) const { flightRepo.setFlightPrice(flightId, newPrice); }
void AdminService::modifyFlightTotalSeats(const unsigned int flightId, const unsigned int newTotalSeats) const { flightRepo.setFlightTotalSeats(flightId, newTotalSeats); }
void AdminService::deleteFlight(const unsigned int flightId) const {
    const Flight *flight = flightRepo.getById(flightId);
    unsigned int departureAirportId = flight->getDepartureAirportId();
    unsigned int arrivalAirportId = flight->getArrivalAirportId();
    airportRepo.decreaseUsages(departureAirportId);
    airportRepo.decreaseUsages(arrivalAirportId);
    flightRepo.remove(flightId);

}
