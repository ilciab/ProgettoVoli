//
// Created by ilciab on 11/20/25.
//

#ifndef PROGETTOVOLI_FLIGHTREPOSITORY_H
#define PROGETTOVOLI_FLIGHTREPOSITORY_H
#include "RepositoryInterface.h"
#include "../Domain/Flight.h"


class FlightRepository : public RepositoryInterface<Flight> {

    std::vector<std::unique_ptr<Flight> > flights;
    Flight *getById_internal(unsigned int id) override;

    IdGenerator idGen;
    std::string path;

public:
    explicit FlightRepository(const std::string &path)
        : path(path) {
        load();
    }

    const Flight *getById(unsigned int id) const override;
    void remove(unsigned int id) override;
    void write() override;
    void load() override;
    std::vector<const Flight *> getAll() override;

    void setFlightDepartureAirport(unsigned int flightId, unsigned int departureAirportId);
    void setFlightArrivalAirport(unsigned int flightId, unsigned int arrivalAirportId);
    void setFlightDepartureTime(unsigned int flightId, std::chrono::system_clock::time_point departureTime);
    void setFlightArrivalTime(unsigned int flightId, std::chrono::system_clock::time_point arrivalTime);
    void setFlightPrice(unsigned int flightId, float price);
    void setFlightTotalSeats(unsigned int flightId, unsigned int totalSeats);
    void setBookedSeats(unsigned int flightId, unsigned int totalSeats);

    unsigned int createFlight(unsigned int departureAirportId, unsigned int arrivalAirportId,
    const std::chrono::system_clock::time_point &departureTimeStr, const std::chrono::system_clock::time_point &arrivalTimeStr, float price, unsigned int totalSeats);
};


#endif //PROGETTOVOLI_FLIGHTREPOSITORY_H
