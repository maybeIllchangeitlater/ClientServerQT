cmake_minimum_required(VERSION 3.5)

project(server VERSION 0.1 LANGUAGES CXX)

add_subdirectory(3rdParty/libpqxx build-pqxx)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        server/server.h
        server/server.cpp
        config/config.h
        repository/stringRepository.h
        repository/stringRepository.cpp
        repository/jsonRepository.h
        repository/jsonRepository.cpp
        repository/binaryRepository.h
        repository/binaryRepository.cpp
        repository/viewRepository.h
        repository/viewRepository.cpp
        service/stringService.h
        service/jsonService.h
        service/binaryService.h
        service/viewService.h
        controller/controller.h
        3rdParty/libpqxx
        ../common/data.h
        ../common/constants/jsonNames.h
        ../common/constants/configJsonNames.h
        ../common/constants/httpHeaderConstants.h
        ../common/constants/BDNames.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(server
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET server APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(server SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(server
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(server PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(server PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(server PRIVATE pqxx)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(server)
endif()
