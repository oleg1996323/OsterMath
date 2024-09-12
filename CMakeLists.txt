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

find_package(QT NAMES Qt6 COMPONENTS Core Widgets LinguistTools REQUIRED)

message(STATUS Qt${QT_VERSION_MAJOR})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets LinguistTools REQUIRED)

set(TS_FILES OsterMath_ru_RU.ts)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/lib/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/lib/Debug)

message(STATUS ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG})

file(GLOB_RECURSE OSTER_WIDGETS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/*.h
    )

file(GLOB_RECURSE PROJECT_SOURCES_KERNEL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/kernel/*.h
    )

file(GLOB_RECURSE PROJECT_SOURCES_UTILITIES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/utilities/*.h
    )

file(GLOB_RECURSE PROJECT_SOURCES_STYLES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/styles/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/styles/*.h
    )

file(GLOB_RECURSE VARMODEL_SOURCES_MODEL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/model/**.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/model/**.h
    )

file(GLOB_RECURSE MENUWIDGETS_SOURCES_MODEL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/menuwidgets/**.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/menuwidgets/**.h
    )

file(GLOB_RECURSE DATAVIEW_SOURCES_MODEL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dataview/**.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/dataview/**.h
    )

file(GLOB PROJECT_SOURCES_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    )

file(GLOB PROJECT_SOURCES_RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/res/*.qrc
    ${TS_FILES}
)
#file(GLOB_RECURSE PROJECT_SOURCES
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/res/*.qrc
#    ${TS_FILES}
#    )

set(VARMODEL_SOURCES ${VARMODEL_SOURCES_MODEL})
set(PROJECT_SOURCES ${PROJECT_SOURCES_UTILITIES}
    ${PROJECT_SOURCES_INCLUDE}
    ${PROJECT_SOURCES_RESOURCES}
    ${MENUWIDGETS_SOURCES_MODEL}
    ${DATAVIEW_SOURCES_MODEL})



set(ARITHMTREE_DIR $ENV{HOME}/Electrolisys/arithmetictree)
find_library(ARITHMTREE_LIB NAMES libarithmetictree.a arithmetictree PATHS ${ARITHMTREE_DIR}/lib/ui/${CMAKE_BUILD_TYPE} REQUIRED)
find_library(ARITHMTREE_EXC_LIB NAMES libexceptions.a exceptions PATHS ${ARITHMTREE_DIR}/lib/ui/${CMAKE_BUILD_TYPE} REQUIRED)
find_library(ANTLR libantlr4-runtime.a PATHS ${ARITHMTREE_DIR}/grammar/lib REQUIRED)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS ${ARITHMTREE_DIR})
message(STATUS ${ARITHMTREE_DIR})

include_directories(
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        /usr/include/c++/11
        ${ARITHMTREE_DIR}/include)

add_library(styles SHARED ${PROJECT_SOURCES_STYLES} ${OSTER_WIDGETS})

target_include_directories(styles PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/styles
					${CMAKE_CURRENT_SOURCE_DIR}/src/widgets
					${CMAKE_CURRENT_SOURCE_DIR}/include/styles
					${CMAKE_CURRENT_SOURCE_DIR}/include/widgets)

target_link_libraries(styles PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

set_property(TARGET styles PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(app SHARED
    ${PROJECT_SOURCES_KERNEL})

target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/kernel
                                ${CMAKE_CURRENT_SOURCE_DIR}/src/styles
                                ${CMAKE_CURRENT_SOURCE_DIR}/include/styles)

target_link_libraries(app PUBLIC styles PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

set_property(TARGET app PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(model SHARED
    ${VARMODEL_SOURCES}
)

set_property(TARGET model PROPERTY POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(model PRIVATE MODEL_SHARED)

target_include_directories(model
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${ARITHMTREE_DIR}/include
        ${ARITHMTREE_DIR}/include/types)

target_link_libraries(model PUBLIC app styles PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets PRIVATE ${ARITHMTREE_LIB} ${ARITHMTREE_EXC_LIB} ${ANTLR})

add_executable(OsterMath
    ${PROJECT_SOURCES}
)

qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_include_directories(OsterMath
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${ARITHMTREE_DIR}/include
        ${ARITHMTREE_DIR}/include/types)

target_link_libraries(OsterMath PUBLIC model PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OsterMath)
endif()
