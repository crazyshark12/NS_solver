cmake_minimum_required(VERSION 3.14)

project(NS_solver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC_FOLDER "${PROJECT_SOURCE_DIR}/src")
set(HDR_FOLDER "${PROJECT_SOURCE_DIR}/hdr")


set(${PROJECT_NAME}_SRC  ${SRC_FOLDER}/abstractsolver.cpp
                         ${SRC_FOLDER}/grid.cpp
                         ${SRC_FOLDER}/macropars.cpp
)

set(${PROJECT_NAME}_HDR  ${HDR_FOLDER}/abstractsolver.h
                         ${HDR_FOLDER}/grid.h
                         ${HDR_FOLDER}/macropars.h
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HDR})

add_subdirectory(example)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D_USE_MATH_DEFINES)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hdr>"
                                                  "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>")