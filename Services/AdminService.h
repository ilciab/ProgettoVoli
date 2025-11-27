//
// Created by ciabu on 30/09/2025.
//

#ifndef ADMINSERVICE_H
#define ADMINSERVICE_H
#include "../Domain/Flight.h"
#include "../Repositories/AirportRepository.h"
#include "../Repositories/FlightRepository.h"
#include "../Repositories/UserRepository.h"


class AdminService {
    UserRepository& userRepo;
    AirportRepository& airportRepo;
    FlightRepository& flightRepo;

public:
explicit AdminService(UserRepository &user_repo, AirportRepository &airport_repo, FlightRepository &flight_repo)
        : userRepo(user_repo),
        airportRepo(airport_repo),
        flightRepo(flight_repo) {}


    std::vector<const User *> getAllUsers() const;
    const User* getUser(unsigned int userId) const;
    void modifyUserName(unsigned int userId, const std::string & newName) const;
    void modifyUserEmail(unsigned int userId, const std::string & newEmail) const;
    void modifyUserLevel(unsigned int userId, const std::string & newLevel);
    void deleteUser(unsigned int userId) const;

    bool createAirport(const std::string& iata, const std::string& nation, const std::string& city, const std::string& name) const;
    std::vector<const Airport *> getAllAirports() const;
    const Airport* getAirport(unsigned int airportId) const;
    void modifyAirportIATA(unsigned int airportId, const std::string & newIata) const;
    void modifyAirportNation(unsigned int airportId, const std::string & newNation) const;
    void modifyAirportCity(unsigned int airportId, const std::string & newCity) const;
    void modifyAirportName(unsigned int airportId, const std::string & newName) const;
    void deleteAirport(unsigned int airportId) const;

    std::vector<const Flight *> getAllFlights();
    const Flight* getFlight(unsigned int flightId);
    bool modifyFlightDepartureAirportId(unsigned int flightId, unsigned int newDepartureAirportId) const;
    bool modifyFlightArrivalAirportId(unsigned int flightId, unsigned int newArrivalAirportId) const;
    bool modifyFlightDepartureTime(unsigned int flightId, std::string newDepartureTime) const;
    bool modifyFlightArrivalTime(unsigned int flightId, std::string newArrivalTime) const;
    void modifyFlightPrice(unsigned int flightId, float newPrice) const;
    void modifyFlightTotalSeats(unsigned int flightId, unsigned int newTotalSeats) const;
    void deleteFlight(unsigned int flightId) const;

    void close() {
        airportRepo.write();
        flightRepo.write();
    }
};



#endif //ADMINSERVICE_H
