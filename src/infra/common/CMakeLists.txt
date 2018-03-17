cmake_minimum_required(VERSION 3.2)

set(FUTURAMA_INFRA_COMMON_TARGET_NAME "futurama-infra-common")

set(CMAKE_CXX_STANDARD 17)

project("Futurama Infra Common Library")

add_library(${FUTURAMA_INFRA_COMMON_TARGET_NAME}
    STATIC
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/infra/clihelpers.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/infra/concurrentautoincrement.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/infra/functionalerror.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/infra/functionalerrorcategory.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/infra/point.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/infra/randomnumbergenerator.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/infra/subject.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/fut/infra/technicalerror.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/infra/functionalerrorcategory.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/infra/randomnumbergenerator.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/infra/subject.cpp")

target_include_directories(${FUTURAMA_INFRA_COMMON_TARGET_NAME}
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
