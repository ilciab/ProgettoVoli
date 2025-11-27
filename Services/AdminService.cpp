//
// Created by ciabu on 30/09/2025.
//

#include "AdminService.h"

#include <iostream>

std::vector<const User *> AdminService::getAllUsers() const { return userRepo.getAll(); }
const User *AdminService::getUser(const unsigned int userId) const { return userRepo.getById(userId); }

void AdminService::modifyUserName(const unsigned int userId, const std::string &newName) const { userRepo.setUserName(userId, newName);}
void AdminService::modifyUserEmail(const unsigned int userId, const std::string &newEmail) const { userRepo.setUserEmail(userId, newEmail); }
void AdminService::modifyUserLevel(const unsigned int userId, const std::string &newLevel) {} //fixme

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


std::vector<const Flight *> AdminService::getAllFlights() { return flightRepo.getAll(); }
const Flight * AdminService::getFlight(const unsigned int flightId) { return flightRepo.getById(flightId); }

bool AdminService::modifyFlightDepartureAirportId(const unsigned int flightId, const unsigned int newDepartureAirportId) const {
    if (airportRepo.getById(newDepartureAirportId) == nullptr)
        return false;
    const Flight *selectedFlight = flightRepo.getById(flightId);
    if (newDepartureAirportId == selectedFlight->getArrivalAirportId())
        return false;
    flightRepo.setFlightDepartureAirport(flightId, newDepartureAirportId);
    return true;
}

bool AdminService::modifyFlightArrivalAirportId(const unsigned int flightId, const unsigned int newArrivalAirportId) const {
    if (airportRepo.getById(newArrivalAirportId) == nullptr)
        return false;
    const Flight *selectedFlight = flightRepo.getById(flightId);
    if (newArrivalAirportId == selectedFlight->getDepartureAirportId())
        return false;
    flightRepo.setFlightDepartureAirport(flightId, newArrivalAirportId);
    return true;
}

bool AdminService::modifyFlightDepartureTime(unsigned int flightId, std::string newDepartureTime) const {
    //flightRepo.setFlightDepartureTime(flightId, newDepartureTime); //fixme
}

bool AdminService::modifyFlightArrivalTime(unsigned int flightId, std::string newArrivalTime) const {
    //flightRepo.setFlightArrivalTime(flightId, newArrivalTime); //fixme
}

void AdminService::modifyFlightPrice(const unsigned int flightId, const float newPrice) const { flightRepo.setFlightPrice(flightId, newPrice); }
void AdminService::modifyFlightTotalSeats(const unsigned int flightId, const unsigned int newTotalSeats) const { flightRepo.setFlightTotalSeats(flightId, newTotalSeats); }
void AdminService::deleteFlight(const unsigned int flightId) const { flightRepo.remove(flightId); }
