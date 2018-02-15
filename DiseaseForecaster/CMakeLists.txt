cmake_minimum_required(VERSION 3.8)
project(DiseaseForecaster)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Analyse.cpp
        Analyse.h
        HealthPrint.cpp
        HealthPrint.h
        Interface.cpp
        Interface.h
        Log.cpp
        Log.h
        main.cpp
        MenuInterface.cpp
        MenuInterface.h
        PotentialDisease.cpp
        PotentialDisease.h
        SearchInterface.cpp
        SearchInterface.h)

add_executable(DiseaseForecaster ${SOURCE_FILES})