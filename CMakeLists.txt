cmake_minimum_required(VERSION 3.31)
project(ProgettoVoli)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProgettoVoli main.cpp
        Domain/User.h
        Repositories/RepositoryInterface.h
        Repositories/UserRepository.cpp
        Repositories/UserRepository.h
        Utils/IdGenerator.h
        Ui/CLI.cpp
        Ui/CLI.h
        Services/AuthService.cpp
        Services/AuthService.h
        Domain/Customer.h
        Services/AdminService.cpp
        Services/AdminService.h
        Domain/Admin.h
        main.cpp
        main.cpp
        Enums/UserRole.h
        Enums/CustomerLevel.h
        Enums/AdminLevel.h
        Domain/UserStruct.h
        Domain/Flight.h
        Domain/Airport.h
        Repositories/AirportRepository.cpp
        Repositories/AirportRepository.h
        Utils/RepositoryUtils.h
        Repositories/FlightRepository.cpp
        Repositories/FlightRepository.h
        Utils/RepositoryUtils.cpp
)
