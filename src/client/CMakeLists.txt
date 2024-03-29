cmake_minimum_required(VERSION 3.5)

project(client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

set(PROJECT_SOURCES
        main.cpp
        view/mainwindow.cpp
        view/mainwindow.h
        view/mainwindow.ui
        view/stringGenerationPopup.h
        view/stringGenerationPopup.cpp
        view/stringGenerationPopup.ui
        view/dataGenerationPopup.h
        view/dataGenerationPopup.cpp
        view/dataGenerationPopup.ui
        view/viewShowPopup.h
        view/viewShowPopup.cpp
        view/viewShowPopup.ui
        view/binaryViewPopup.h
        view/binaryViewPopup.cpp
        view/binaryViewPopup.ui
        client/client.h
        client/client.cpp
        ../common/randomStringGenerator.h
        ../common/dateTime.h
        ../common/constants/URI.h
        ../common/constants/httpHeaderConstants.h
        ../common/constants/jsonNames.h
        utility/requestGenerator.h
        ../common/data.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(client
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET client APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(client SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(client
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(client)
endif()
