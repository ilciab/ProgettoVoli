//
// Created by ilciab on 11/16/25.
//

#ifndef PROGETTOVOLI_VOLO_H
#define PROGETTOVOLI_VOLO_H
#include <chrono>


class Flight {
    const unsigned int id;
    unsigned int departureAirportId;
    unsigned int arrivalAirportId;
    std::chrono::system_clock::time_point departureTime;
    std::chrono::system_clock::time_point arrivalTime;
    float price;
    unsigned int totalSeats;
    unsigned int bookedSeats;


public:
    unsigned int getId() const { return id; }
    unsigned int getDepartureAirportId() const { return departureAirportId; }
    unsigned int getArrivalAirportId() const { return arrivalAirportId; }
    std::chrono::system_clock::time_point getDepartureTime() const { return departureTime; }
    std::chrono::system_clock::time_point getArrivalTime() const { return arrivalTime; }
    float getPrice() const { return price; }
    unsigned int getTotalSeats() const { return totalSeats; }
    unsigned int getBookedSeats() const { return bookedSeats; }


    void setDepartureAirportId(const unsigned int departureAirportId) { this->departureAirportId = departureAirportId; }
    void setArrivalAirportId(const unsigned int arrivalAirportId) { this->arrivalAirportId = arrivalAirportId; }
    void setDepartureTime(const std::chrono::system_clock::time_point &departureTime) { this->departureTime = departureTime; }
    void setArrivalTime(const std::chrono::system_clock::time_point &arrivalTime) { this->arrivalTime = arrivalTime; }
    void setPrice(const float price) { this->price = price; }
    void setTotalSeats(const unsigned int totalSeats) { this->totalSeats = totalSeats; }


    Flight(const unsigned int id, const unsigned int departure_airport_id, const unsigned int arrival_airport_id,
           const std::chrono::system_clock::time_point &departure_time,
           const std::chrono::system_clock::time_point &arrival_time, const float price, const unsigned int total_seats,
           const unsigned int booked_seats)
        : id(id),
          departureAirportId(departure_airport_id),
          arrivalAirportId(arrival_airport_id),
          departureTime(departure_time),
          arrivalTime(arrival_time),
          price(price),
          totalSeats(total_seats),
          bookedSeats(booked_seats) {
    }

    Flight(const unsigned int id, const unsigned int departure_airport_id, const unsigned int arrival_airport_id,
           const std::chrono::system_clock::time_point &departure_time,
           const std::chrono::system_clock::time_point &arrival_time, const float price, const unsigned int total_seats)
        : id(id),
          departureAirportId(departure_airport_id),
          arrivalAirportId(arrival_airport_id),
          departureTime(departure_time),
          arrivalTime(arrival_time),
          price(price),
          totalSeats(total_seats) {
        bookedSeats = 0;
    }
};


#endif //PROGETTOVOLI_VOLO_H
