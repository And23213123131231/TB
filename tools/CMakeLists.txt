cmake_minimum_required(VERSION 3.16)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(TOOLS_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/DataStructures.h
    ${CMAKE_CURRENT_LIST_DIR}/DataProcessor.h

    ${CMAKE_CURRENT_LIST_DIR}/NetworkStructures.h
    PARENT_SCOPE
)

set(TOOLS_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/DataStructures.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DataProcessor.cpp

    ${CMAKE_CURRENT_LIST_DIR}/NetworkStructures.cpp
    PARENT_SCOPE
)
