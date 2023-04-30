cmake_minimum_required(VERSION 3.16)

project(ticket_server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(Qt6 REQUIRED COMPONENTS Qml)

# ===================== App HEADER/SOURCES  =====================
set(SOURCE
   ${CMAKE_CURRENT_LIST_DIR}/TicketServer.cpp
   ${CMAKE_CURRENT_LIST_DIR}/network/Connection.cpp
   ${CMAKE_CURRENT_LIST_DIR}/database/TicketsDatabase.cpp
)
set(HEADERS
   ${CMAKE_CURRENT_LIST_DIR}/TicketServer.h
   ${CMAKE_CURRENT_LIST_DIR}/network/Connection.h
   ${CMAKE_CURRENT_LIST_DIR}/database/TicketsDatabase.h
)

# ===================== Unit testing HEADER/SOURCES  =====================
set(TICKET_SERVER_UT_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/ServerTestMain.h
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/TicketsDatabase_Test.h
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/Connection_Test.h
    PARENT_SCOPE
)

set(TICKET_SERVER_UT_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/ServerTestMain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/TicketsDatabase_Test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/unit_test/Connection_Test.cpp
    PARENT_SCOPE
)

# ===================== Executable or Library =====================
if(BUILD_AS_MODULE)
    target_sources(ticket_server PRIVATE ${SOURCE} ${HEADERS})
    set(TARGET_BUILD ticket_server)
else()
    include(${CMAKE_CURRENT_SOURCE_DIR}/../shared_functions.cmake)
    add_module(tools)

    add_executable(ticket_server
        ${SOURCE}
        ${HEADERS}
        main.cpp
    )

    set(TARGET_BUILD ticket_server)

    set_target_properties(ticket_server PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )
endif()

target_link_libraries(${TARGET_BUILD}
    PUBLIC
    Qt::Core
    Qt::WebSockets
)

set(server_resources
    FilmTicket.js
    localhost.cert
    localhost.key
)

qt6_add_resources(${TARGET_BUILD} "server_resources"
    PREFIX
        "/"
    FILES
        ${server_resources}
)

