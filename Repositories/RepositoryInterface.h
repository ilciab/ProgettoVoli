//
// Created by ciabu on 23/09/2025.
//

#ifndef IREPOSITORY_H
#define IREPOSITORY_H
#include <optional>
#include <vector>

#include "../Domain/User.h"
#include "../Utils/IdGenerator.h"


template <typename T>

class RepositoryInterface {

protected:
    virtual T* getById_internal(unsigned int id) = 0;

public:
    virtual const T* getById(unsigned int id) const = 0;
    virtual void remove(unsigned int id) = 0;
    virtual void write() = 0;
    virtual void load() = 0;
    virtual std::vector<const T *> getAll() = 0;
    virtual ~RepositoryInterface() = default;
};



#endif //IREPOSITORY_H
