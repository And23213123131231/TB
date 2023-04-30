cmake_minimum_required(VERSION 3.16)

function(add_module name)
    set(module_path ${CMAKE_CURRENT_SOURCE_DIR}/../${name}/)
    include(${module_path}/CMakeLists.txt)
    add_subdirectory(${module_path} "${CMAKE_CURRENT_BINARY_DIR}/${name}")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

    string(TOUPPER ${name} INTERNAL_NAME)
    set(SOURCE
        ${SOURCE}
        ${${INTERNAL_NAME}_SOURCE}
        PARENT_SCOPE
    )

    set(HEADERS
        ${HEADERS}
        ${${INTERNAL_NAME}_HEADERS}
        PARENT_SCOPE
    )
endfunction()
