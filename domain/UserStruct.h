//
// Created by ilciab on 11/14/25.
//

#ifndef PROGETTOVOLI_LOGINRESULT_H
#define PROGETTOVOLI_LOGINRESULT_H
#include <optional>

#include "../enums/UserRole.h"

#endif //PROGETTOVOLI_LOGINRESULT_H

struct UserStruct {
    std::optional<unsigned int> id;
    UserRole role;
    unsigned int responseCode;
};

//todo levare optional e usare reponseCode per vedere se la risposta è valida, aggiustare nome fare magari AuthResponse o cose del genere.