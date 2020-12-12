cmake_minimum_required(VERSION 3.10)
project(SOM_C)

set(CMAKE_C_STANDARD 99)

add_executable(SOM_C main.c analysisTools.h processEntryData.h randomizeNumbers.h weightMapCreation.h calculateDistances.h modelTraining.h)

target_link_libraries(SOM_C m)