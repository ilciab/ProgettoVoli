//
// Created by ilciab on 11/16/25.
//

#ifndef PROGETTOVOLI_AIRPORT_H
#define PROGETTOVOLI_AIRPORT_H
#include <string>


class Airport {
    const unsigned int id;
    std::string name;
    std::string nation;
    std::string city;
    std::string iata;

public:
    const unsigned int getId() const {return id;}

    const std::string &getName() const {return name;}

    const std::string &getNation() const {return nation;}

    const std::string &getCity() const {return city;}

    const std::string &getIata() const {return iata;}

    Airport(unsigned int id, const std::string &name, const std::string &nation, const std::string &city,
            const std::string &iata)
        : id(id),
          name(name),
          nation(nation),
          city(city),
          iata(iata) {
    }
};


#endif //PROGETTOVOLI_AIRPORT_H