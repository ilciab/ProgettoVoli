//
// Created by ciabu on 30/09/2025.
//

#include "AdminService.h"

#include <iostream>
#include <ostream>

const std::vector<const User *> AdminService::getAllUsers() { return userRepo.getAll(); }
const User *AdminService::getUser(const unsigned int userId) const { return userRepo.getById(userId); }

void AdminService::modifyUserName(unsigned int userId, const std::string &newName) const { userRepo.setUserName(userId, newName);}

void AdminService::modifyUserEmail(unsigned int userId, const std::string &newEmail) const { userRepo.setUserEmail(userId, newEmail); }

void AdminService::modifyUserLevel(unsigned int userId, const std::string &newLevel) {}

void AdminService::deleteUser(unsigned int userId) const { userRepo.remove(userId); }

const Airport *AdminService::getAirport(unsigned int airportId) { return airportRepo.getById(airportId); }
const std::vector<const Airport *> AdminService::getAllAirports() { return airportRepo.getAll(); }

void AdminService::modifyAirportName(const unsigned int airportId, const std::string &newName) const { airportRepo.setAirportName(airportId, newName); }
void AdminService::modifyAirportNation(const unsigned int airportId, const std::string &newNation) const { airportRepo.setAirportNation(airportId, newNation); }
void AdminService::modifyAirportCity(const unsigned int airportId, const std::string &newCity) const { airportRepo.setAirportCity(airportId, newCity); }
void AdminService::modifyAirportIATA(const unsigned int airportId, const std::string &newIata) const { airportRepo.setAirportIata(airportId, newIata); }

void AdminService::deleteAirport(const unsigned int airportId) {}
