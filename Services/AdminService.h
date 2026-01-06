//
// Created by ciabu on 30/09/2025.
//

#ifndef ADMINSERVICE_H
#define ADMINSERVICE_H
#include "../Domain/Flight.h"
#include "../Repositories/AirportRepository.h"
#include "../Repositories/FlightRepository.h"
#include "../Repositories/ReservationRepository.h"
#include "../Repositories/UserRepository.h"


class AdminService {
    UserRepository& userRepo;
    AirportRepository& airportRepo;
    FlightRepository& flightRepo;
    ReservationRepository& reservationRepo;

public:
explicit AdminService(UserRepository &userRepo, AirportRepository &airportRepo, FlightRepository &flightRepo, ReservationRepository &reservationRepo)
        : userRepo(userRepo),
        airportRepo(airportRepo),
        flightRepo(flightRepo),
        reservationRepo(reservationRepo) {}

    std::vector<const User *> getAllUsers() const;
    const User* getUser(unsigned int userId) const;
    void modifyUserName(unsigned int userId, const std::string & newName) const;
    void modifyUserEmail(unsigned int userId, const std::string & newEmail) const;
    void deleteUser(unsigned int userId) const;

    bool createAirport(const std::string& iata, const std::string& nation, const std::string& city, const std::string& name) const;
    std::vector<const Airport *> getAllAirports() const;
    const Airport* getAirport(unsigned int airportId) const;
    void modifyAirportIATA(unsigned int airportId, const std::string & newIata) const;
    void modifyAirportNation(unsigned int airportId, const std::string & newNation) const;
    void modifyAirportCity(unsigned int airportId, const std::string & newCity) const;
    void modifyAirportName(unsigned int airportId, const std::string & newName) const;
    void deleteAirport(unsigned int airportId) const;


    bool createFlight(unsigned int departureAirportId, unsigned int arrivalAirportId,
        const std::chrono::system_clock::time_point &departureTime, const std::chrono::system_clock::time_point &arrivalTime, float price, unsigned int totalSeats) const;
    std::vector<const Flight *> getAllFlights() const;
    const Flight* getFlight(unsigned int flightId) const;
    bool modifyFlightDepartureAirportId(unsigned int flightId, unsigned int newDepartureAirportId) const;
    bool modifyFlightArrivalAirportId(unsigned int flightId, unsigned int newArrivalAirportId) const;
    void modifyFlightDepartureTime(unsigned int flightId, const std::chrono::system_clock::time_point &newDepartureTime) const;
    void modifyFlightArrivalTime(unsigned int flightId, const std::chrono::system_clock::time_point &newArrivalTime) const;
    void modifyFlightPrice(unsigned int flightId, float newPrice) const;
    void modifyFlightTotalSeats(unsigned int flightId, unsigned int newTotalSeats) const;
    void deleteFlight(unsigned int flightId) const;

    void deleteReservation(unsigned int reservationId) const;

    void close() const {
        airportRepo.write();
        flightRepo.write();
    }
};



#endif //ADMINSERVICE_H
