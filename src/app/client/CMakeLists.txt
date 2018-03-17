cmake_minimum_required(VERSION 3.2)

set(FUTURAMA_APP_CLIENT_TARGET_NAME "futurama-app-client")

set(CMAKE_CXX_STANDARD 17)

project("Futurama App Client Library")

add_library(${FUTURAMA_APP_CLIENT_TARGET_NAME}
    STATIC
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/app/client.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/app/game.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/app/gamemanager.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/app/scangenerator.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/app/sectorgenerator.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/app/client.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/app/game.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/app/gamemanager.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/app/scangenerator.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/app/sectorgenerator.cpp")

target_include_directories(${FUTURAMA_APP_CLIENT_TARGET_NAME}
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(${FUTURAMA_APP_CLIENT_TARGET_NAME}
    "futurama-domain-common"
    "futurama-infra-common")
