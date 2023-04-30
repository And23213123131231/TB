cmake_minimum_required(VERSION 3.16)

project(TicketBooking VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

set(BUILD_AS_MODULE ON)

# client library
add_library(booking_client STATIC)
add_subdirectory(booking_client)

# server library
add_library(ticket_server STATIC)
add_subdirectory(ticket_server)


# shared functional
add_subdirectory(tools)

add_executable(appTicketBooking
    ${TOOLS_SOURCE}
    ${TOOLS_HEADERS}
    main.cpp)


set_target_properties(appTicketBooking PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_ABIS "arm64-v8a;x86"
)

find_package(Qt6 COMPONENTS Core Gui Quick Qml WebSockets REQUIRED)

target_link_libraries(appTicketBooking
    PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::Qml
    Qt::WebSockets

    PRIVATE
    Qt6::Qml

    # include independent projects, as a libraries for standalone application
    ticket_server
    booking_client
)
