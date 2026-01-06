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
    unsigned int usages = 0;

public:
    unsigned int getId() const { return id; }
    const std::string &getName() const { return name; }
    const std::string &getNation() const { return nation; }
    const std::string &getCity() const { return city; }
    const std::string &getIata() const { return iata; }
    unsigned int getUsages() const { return usages; } //todo implementare sta roba

    void setName(const std::string &name) { this->name = name; }
    void setNation(const std::string &nation) { this->nation = nation; }
    void setCity(const std::string &city) { this->city = city; }
    void setIata(const std::string &iata) { this->iata = iata; }
    void setUsages(const unsigned int usages) { this-> usages = usages; }

    Airport(unsigned int id, const std::string &iata, const std::string &nation, const std::string &city,
            const std::string &name)
        : id(id),
          name(name),
          nation(nation),
          city(city),
          iata(iata) {
    }
};


#endif //PROGETTOVOLI_AIRPORT_H
