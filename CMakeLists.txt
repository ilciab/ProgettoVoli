cmake_minimum_required(VERSION 3.31)
project(ProgettoVoli)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProgettoVoli main.cpp
        domain/User.cpp
        domain/User.h
        repo/RepositoryInterface.h
        repo/UserRepository.cpp
        repo/UserRepository.h
        util/idGenerator.cpp
        util/idGenerator.h
        ui/CLI.cpp
        ui/CLI.h
        service/AuthService.cpp
        service/AuthService.h
)
