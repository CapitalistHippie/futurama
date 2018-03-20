cmake_minimum_required(VERSION 3.2)

set(FUTURAMA_DOMAIN_COMMON_TARGET_NAME "futurama-domain-common")

set(CMAKE_CXX_STANDARD 17)

project("Futurama Domain Common Library")

add_library(${FUTURAMA_DOMAIN_COMMON_TARGET_NAME}
    STATIC
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/events/gamestarted.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/events/movedtofield.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/events/movedtoheadquarters.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/events/movedtosector.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/events/packagepickedup.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/game.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/gamestate.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/meeting.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/package.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/player.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/scan.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/scansector.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/sector.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/sectorfield.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/sectorfieldthing.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/ship.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/domain/models/universe.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/placeholder.cpp")

target_include_directories(${FUTURAMA_DOMAIN_COMMON_TARGET_NAME}
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(${FUTURAMA_DOMAIN_COMMON_TARGET_NAME}
    "futurama-infra-common")
