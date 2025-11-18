//
// Created by ciabu on 30/09/2025.
//

#include "AdminService.h"

#include <iostream>
#include <ostream>

const std::vector<const User *> AdminService::getAllUsers() {
    return userRepo.getAll();
}
const User *AdminService::getUser(const unsigned int userId) { return userRepo.getById(userId); }

void AdminService::modifyUserName(unsigned int userId, const std::string &newName) {
    userRepo.setUserName(userId, newName);
}

void AdminService::modifyUserEmail(unsigned int userId, const std::string &newEmail) {
    userRepo.setUserEmail(userId, newEmail);
}

void AdminService::modifyUserLevel(unsigned int userId, const std::string &newLevel) {
}

void AdminService::deleteUser(unsigned int userId) { userRepo.remove(userId); }

const std::vector<const Airport *> AdminService::getAllAirports() {
    return airportRepo.getAll();
}

const Airport * AdminService::getAirport(unsigned int airportId) { return airportRepo.getById(airportId); }

void AdminService::modifyAirportName(unsigned int airportId, const std::string &newName) { return airportRepo.setAirportName()}

void AdminService::modifyAirpotyNation(unsigned int airportId, const std::string &newNation) {
}

void AdminService::modifyAirportCity(unsigned int airportId, const std::string &newCity) {
}

void AdminService::modifyAirportIATA(unsigned int airportId, const std::string &newIata) {
}

void AdminService::deleteAirport(unsigned int airportId) {
}
