cmake_minimum_required(VERSION 3.2)

set(FUTURAMA_UI_CLIENT_CLI_TARGET_NAME "futurama-ui-clientcli")

set(CMAKE_CXX_STANDARD 17)

project("Futurama UI Client CLI")

add_executable(${FUTURAMA_UI_CLIENT_CLI_TARGET_NAME}
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/clientcli.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/clientcli.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/command.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/commandparser.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/commandparser.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/statehandler.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/statehandlerbase.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/statehandlerbase.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/statehandlerheadquarters.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/statehandlerheadquarters.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/statehandlermenu.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/statehandlermenu.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/statehandlerontheway.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/fut/ui/statehandlerontheway.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp")

target_include_directories(${FUTURAMA_UI_CLIENT_CLI_TARGET_NAME}
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")

target_link_libraries(${FUTURAMA_UI_CLIENT_CLI_TARGET_NAME}
    "futurama-app-client"
    "futurama-infra-common")
