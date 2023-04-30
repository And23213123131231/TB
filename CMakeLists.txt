cmake_minimum_required(VERSION 3.16)

project(TicketBooking VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

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


# ===================== App target  =====================
set_target_properties(appTicketBooking PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_ABIS "arm64-v8a;x86"
)

target_compile_options(appTicketBooking PRIVATE -Wall -Wextra -Wpedantic -Werror)

find_package(Qt6 COMPONENTS Core Gui Quick Qml WebSockets Test REQUIRED)

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


# ===================== Tests target  =====================
add_executable(TestApp
    ${TOOLS_SOURCE}
    ${TOOLS_HEADERS}
    ${TOOLS_UT_SOURCE}
    ${TOOLS_UT_HEADERS}
    ${BOOKING_CLIENT_UT_SOURCE}
    ${BOOKING_CLIENT_UT_HEADERS}
    ${TICKET_SERVER_UT_SOURCE}
    ${TICKET_SERVER_UT_HEADERS}
    tests_main.cpp)

target_link_libraries(TestApp
    PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::Qml
    Qt::WebSockets

    PRIVATE
    Qt6::Qml
    Qt6::Test

    # include independent projects, as a libraries for standalone application
    ticket_server
    booking_client
)

set_target_properties(TestApp PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_ABIS "arm64-v8a;x86"
)

