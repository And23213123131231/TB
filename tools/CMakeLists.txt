cmake_minimum_required(VERSION 3.16)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ===================== App HEADER/SOURCES  =====================
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

# ===================== Unit testing HEADER/SOURCES  =====================
set(TOOLS_UT_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/ToolsTestMain.h
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/DataStructures_Test.h
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/NetworkStructures_Test.h
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/DataProcessor_Test.h

    PARENT_SCOPE
)

set(TOOLS_UT_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/ToolsTestMain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/DataStructures_Test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/NetworkStructures_Test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/DataProcessor_Test.cpp
    PARENT_SCOPE
)
