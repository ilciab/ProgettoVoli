//
// Created by ciabu on 23/09/2025.
//

#ifndef IREPOSITORY_H
#define IREPOSITORY_H
#include <optional>
#include <vector>

#include "../domain/User.h"
#include "../util/IdGenerator.h"


template <typename T>

class RepositoryInterface {

public:

    virtual std::vector<T> getAll() = 0;
    virtual unsigned int* getById(int id) = 0;
    virtual void remove(int id) = 0;
    virtual void add(const T&) = 0;
    virtual void write() = 0;
    virtual void load() = 0;

    virtual ~RepositoryInterface() = default;
};



#endif //IREPOSITORY_H
