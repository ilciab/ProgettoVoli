//
// Created by ciabu on 03/12/2025.
//

#ifndef CLI_H
#define CLI_H


#include "../Repositories/AirportRepository.h";

class CustomerService{
    private:
        AirportRepository& airportRepo;

    public:
        explicit CustomerService(AirportRepository& airportRepo) : airportRepo(airportRepo) {};
};


#endif //CLI_H
