cmake_minimum_required(VERSION 3.15)

project(OsterMath VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
set(CMAKE_GLOBAL_AUTORCC_TARGET)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt5 COMPONENTS Core Widgets LinguistTools REQUIRED)

message(STATUS Qt${QT_VERSION_MAJOR})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets LinguistTools REQUIRED)

set(TS_FILES OsterMath_ru_RU.ts)

file(GLOB_RECURSE PROJECT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/**.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/res/*.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OsterMath
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET OsterMath APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(OsterMath SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(OsterMath
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

set(ARITHMTREE_DIR $ENV{HOME}/Electrolisys/arithmetictree)

find_library(ARITHMTREE_LIB NAMES libarithmetictree.a arithmetictree PATHS $ENV{HOME}/Electrolisys/arithmetictree/lib REQUIRED)
find_library(ANTLR libantlr4-runtime.a PATHS ${ARITHMTREE_DIR}/grammar/lib REQUIRED)

include_directories(
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        /usr/include/c++/11
        ${ARITHMTREE_DIR}/include)

target_include_directories(OsterMath
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${ARITHMTREE_DIR}/include)

target_link_libraries(OsterMath PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets PUBLIC ${ARITHMTREE_LIB} ${ANTLR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OsterMath)
endif()
