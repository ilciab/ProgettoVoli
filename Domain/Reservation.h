//
// Created by ilciab on 12/4/25.
//

#ifndef PROGETTOVOLI_RESERVATION_H
#define PROGETTOVOLI_RESERVATION_H

#endif //PROGETTOVOLI_RESERVATION_H

class Reservation {
private:
    unsigned int id;
    unsigned int ownerUserId;
    unsigned int flightId;

public:
    Reservation(const unsigned int id, const unsigned int ownerUserId, const unsigned int flightId)
        : id(id),
          ownerUserId(ownerUserId),
          flightId(flightId) {
    }

    unsigned int getId() const {
        return id;
    }

    unsigned int getOwnerUserId() const {
        return ownerUserId;
    }

    unsigned int getFlightId() const {
        return flightId;
    }
};
