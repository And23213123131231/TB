cmake_minimum_required(VERSION 3.16)

project(booking_client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ===================== App HEADER/SOURCES  =====================
set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/ModulesKeeper.h
    ${CMAKE_CURRENT_LIST_DIR}/BookingClient.h

    ${CMAKE_CURRENT_LIST_DIR}/network/Client.h

    ${CMAKE_CURRENT_LIST_DIR}/controllers/StackViewController.h
    ${CMAKE_CURRENT_LIST_DIR}/controllers/MoviesModelController.h
    ${CMAKE_CURRENT_LIST_DIR}/controllers/TheatersModelController.h
    ${CMAKE_CURRENT_LIST_DIR}/controllers/TicketsModelController.h
)

set(SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/ModulesKeeper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BookingClient.cpp

    ${CMAKE_CURRENT_LIST_DIR}/network/Client.cpp

    ${CMAKE_CURRENT_LIST_DIR}/controllers/StackViewController.cpp
    ${CMAKE_CURRENT_LIST_DIR}/controllers/MoviesModelController.cpp
    ${CMAKE_CURRENT_LIST_DIR}/controllers/TheatersModelController.cpp
    ${CMAKE_CURRENT_LIST_DIR}/controllers/TicketsModelController.cpp
)

# ===================== Client HEADER/SOURCES  =====================
#set(BOOKING_CLIENT_UT_HEADERS
#    PARENT_SCOPE
#)

#set(BOOKING_CLIENT_UT_SOURCE
#    PARENT_SCOPE
#)

# ===================== QML Templates  =====================
set(BOOKING_CLIENT_QML_MODULE_NAME TicketTemplates)
set(BOOKING_CLIENT_QML_LIST
    qml/templates/BasicScreen.qml
    qml/templates/BasicButton.qml
)

# ===================== Executable or Library =====================
if(BUILD_AS_MODULE)
    target_sources(booking_client PRIVATE ${SOURCE} ${HEADERS})
    set(TARGET_BUILD booking_client)

else()
    include(${CMAKE_CURRENT_SOURCE_DIR}/../shared_functions.cmake)
    add_module(tools)

    add_executable(booking_client
        ${SOURCE}
        ${HEADERS}
        main.cpp
    )

set(TARGET_BUILD booking_client)

set_target_properties(booking_client PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_ABIS "arm64-v8a;x86"
)
endif()

# ===================== External linking =====================
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml WebSockets)
target_link_libraries(${TARGET_BUILD}
    PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::Qml
    Qt::WebSockets

    PRIVATE
    Qt6::Quick
)

# ===================== QML Modules  =====================
if(BUILD_AS_MODULE)
    qt6_add_qml_module(booking_client_qml_stanalone
        URI ${BOOKING_CLIENT_QML_MODULE_NAME}
        VERSION 1.0
        PLUGIN_TARGET booking_client_qml_stanalone
        OUTPUT_DIRECTORY "../${BOOKING_CLIENT_QML_MODULE_NAME}"
        QML_FILES
        ${BOOKING_CLIENT_QML_LIST}
    )

else()
    qt6_add_qml_module(booking_client
        URI ${BOOKING_CLIENT_QML_MODULE_NAME}
        VERSION 1.0
        QML_FILES ${BOOKING_CLIENT_QML_LIST}
    )
endif()

# ===================== Application  resources, QML  =====================
set(client_resources
    qml/AppSettings.qml
    qml/MoviesScreen.qml
    qml/TheatersScreen.qml
    qml/TicketsScreen.qml
    qml/main.qml
)

qt6_add_resources(${TARGET_BUILD} "client_resources"
    PREFIX
    "/"
    FILES
    ${client_resources}
)







