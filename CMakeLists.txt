cmake_minimum_required(VERSION 3.10)
project(AimGame)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(AimGame main.cpp)

target_link_libraries(AimGame
    SDL2::SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Characters DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Background DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Icon DESTINATION ${CMAKE_BINARY_DIR})