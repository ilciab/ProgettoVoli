//
// Created by ilciab on 11/14/25.
//

#ifndef PROGETTOVOLI_LOGINRESULT_H
#define PROGETTOVOLI_LOGINRESULT_H
#include <optional>

#include "../Enums/AuthResponse.h"
#include "../Enums/UserRole.h"

#endif //PROGETTOVOLI_LOGINRESULT_H

struct UserStruct {
    unsigned int id;
    UserRole role;
    AuthResponse responseCode;
};