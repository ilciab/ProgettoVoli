
#ifndef PROGETTOVOLI_FLIGHTBUILDER_H
#define PROGETTOVOLI_FLIGHTBUILDER_H
#include "../Domain/Flight.h"

class FlightBuilder {
    unsigned int id{};
    unsigned int departureAirportId{};
    unsigned int arrivalAirportId{};
    std::chrono::system_clock::time_point departureTime;
    std::chrono::system_clock::time_point arrivalTime;
    float price{};
    unsigned int totalSeats{};
    unsigned int bookedSeats = 0;

public:
    FlightBuilder& setId(unsigned int id) { this->id = id; return *this; }
    FlightBuilder& setDepartureAirportId(unsigned int id) { this->departureAirportId = id; return *this; }
    FlightBuilder& setArrivalAirportId(unsigned int id) { this->arrivalAirportId = id; return *this; }
    FlightBuilder& setDepartureTime(auto time) { this->departureTime = time; return *this; }
    FlightBuilder& setArrivalTime(auto time) { this->arrivalTime = time; return *this; }
    FlightBuilder& setPrice(float price) { this->price = price; return *this; }
    FlightBuilder& setTotalSeats(unsigned int seats) { this->totalSeats = seats; return *this; }
    FlightBuilder& setBookedSeats(unsigned int seats) { this->bookedSeats = seats; return *this; }

    Flight build() const {
        return Flight(id, departureAirportId, arrivalAirportId, departureTime, arrivalTime, price, totalSeats, bookedSeats);
    }
};


#endif //PROGETTOVOLI_FLIGHTBUILDER_H