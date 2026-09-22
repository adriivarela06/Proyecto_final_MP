cmake_minimum_required(VERSION 3.10.0)
project(asteroides VERSION 0.1.0 LANGUAGES C CXX)
include(../bigs/bigs.cmake)
include_directories(../bigs)
include_directories(Bitmaps)
add_library(particulas Particula.cpp Vector2D.cpp matematicas.cpp listaparticulas.cpp)

add_executable(testparticula testparticula.cpp)
target_link_libraries(testparticula particulas bigs)

add_executable(rebote rebote.cpp) 
target_link_libraries(rebote particulas bigs)

add_executable(testsobrecarga testsobrecarga.cpp)
target_link_libraries(testsobrecarga particulas)

add_executable(testlista testlista.cpp)
target_link_libraries(testlista particulas bigs)

add_executable(rebotes rebotes.cpp) 
target_link_libraries(rebotes particulas bigs)

add_executable(asteroides asteroides.cpp)
target_link_libraries(asteroides particulas bigs)

add_executable(ranking ranking.cpp marcadores.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
