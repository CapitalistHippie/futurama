cmake_minimum_required(VERSION 3.2)

set(FUTURAMA_DAL_COMMON_TARGET_NAME "futurama-dal-common")

set(CMAKE_CXX_STANDARD 17)

project("Futurama DAL Common Library")

add_library(${FUTURAMA_DAL_COMMON_TARGET_NAME}
    STATIC
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/dal/meetingrepository.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/dal/packagefilerepository.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/dal/packagerepository.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/dal/meetingrepository.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/dal/packagefilerepository.cpp")

target_include_directories(${FUTURAMA_DAL_COMMON_TARGET_NAME}
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(${FUTURAMA_DAL_COMMON_TARGET_NAME}
    "futurama-infra-common"
    "futurama-domain-common")
