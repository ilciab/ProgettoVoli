cmake_minimum_required(VERSION 3.31)
project(ProgettoVoli)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProgettoVoli main.cpp
        domain/User.h
        repo/RepositoryInterface.h
        repo/UserRepository.cpp
        repo/UserRepository.h
        util/IdGenerator.h
        ui/CLI.cpp
        ui/CLI.h
        service/AuthService.cpp
        service/AuthService.h
        domain/Customer.h
        service/AdminService.cpp
        service/AdminService.h
        domain/Admin.h
        main.cpp
        main.cpp
        enums/UserRole.h
        enums/CustomerLevel.h
        enums/AdminLevel.h
        domain/UserStruct.h
        domain/Flight.h
        domain/Airport.h
        repo/AirportRepository.cpp
        repo/AirportRepository.h
        util/RepositoryUtils.h
        repo/FlightRepository.cpp
        repo/FlightRepository.h
)
