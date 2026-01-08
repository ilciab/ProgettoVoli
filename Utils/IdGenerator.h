
#ifndef IDGENERATOR_H
#define IDGENERATOR_H
#include <cstdint>
#include <vector>


class IdGenerator {
private:
        unsigned int nextId = 0; //cambiare prendere l'id più grande, mettere un idGenerator per ogni repository
public:
        IdGenerator() = default;
        void setStartingId(const unsigned int id) {nextId = id+1;}
        unsigned int getNextId() {return nextId++;}
};



#endif //IDGENERATOR_H
