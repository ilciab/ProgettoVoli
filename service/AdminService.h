//
// Created by ciabu on 30/09/2025.
//

#ifndef ADMINSERVICE_H
#define ADMINSERVICE_H
#include "../domain/Flight.h"
#include "../repo/AirportRepository.h"
#include "../repo/UserRepository.h"


class AdminService {
    UserRepository& userRepo;
    AirportRepository& airportRepo;

public:
explicit AdminService(UserRepository &user_repo, AirportRepository &airport_repo)
        : userRepo(user_repo),
        airportRepo(airport_repo) {}


    const std::vector<const User *> getAllUsers();
    const User* getUser(unsigned int userId);
    void modifyUserName(unsigned int userId, const std::string & newName);
    void modifyUserEmail(unsigned int userId, const std::string & newEmail);
    void modifyUserLevel(unsigned int userId, const std::string & newLevel);
    void deleteUser(unsigned int userId);

    const std::vector<const Airport *> getAllAirports();
    const Airport* getAirport(unsigned int airportId);
    void modifyAirportName(unsigned int airportId, const std::string & newName);
    void modifyAirpotyNation(unsigned int airportId, const std::string & newNation);
    void modifyAirportCity(unsigned int airportId, const std::string & newCity);
    void modifyAirportIATA(unsigned int airportId, const std::string & newIata);
    void deleteAirport(unsigned int airportId);
};



#endif //ADMINSERVICE_H
