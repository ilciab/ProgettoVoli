//
// Created by ilciab on 11/16/25.
//

#ifndef PROGETTOVOLI_VOLO_H
#define PROGETTOVOLI_VOLO_H
#include <chrono>

#include "Airport.h"


class Flight {
    const unsigned int id;
    const unsigned int departureAirportId;
    const unsigned int arrivalAirportId;
    std::chrono::system_clock::time_point departureTime;
    std::chrono::system_clock::time_point arrivalTime;
    unsigned int price;
    unsigned int totalSeats;
    unsigned int bookedSeats;

public:
    Flight(unsigned int id, unsigned int departure_airport_id, unsigned int arrival_airport_id,
        const std::chrono::system_clock::time_point &departure_time,
        const std::chrono::system_clock::time_point &arrival_time, unsigned int price, unsigned int total_seats)
        : id(id),
          departureAirportId(departure_airport_id),
          arrivalAirportId(arrival_airport_id),
          departureTime(departure_time),
          arrivalTime(arrival_time),
          price(price),
          totalSeats(total_seats){
    }

    //todo
};


#endif //PROGETTOVOLI_VOLO_H