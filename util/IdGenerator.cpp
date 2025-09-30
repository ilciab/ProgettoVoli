//
// Created by ciabu on 23/09/2025.
//

#include "IdGenerator.h"

IdGenerator::IdGenerator() {
    nextId = 0;
}
void IdGenerator::setStartingId(const unsigned int & id) {
    nextId = id+1;
}

unsigned int IdGenerator::getNextId() {
    return nextId++;
}


