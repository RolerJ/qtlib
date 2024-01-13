cmake_minimum_required(VERSION 3.12)

project(
  roler-qtlib
  VERSION 0.1
  LANGUAGES CXX)

include(GNUInstallDirs)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE STRING "Choose Release or Debug" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(MSVC)
  string(APPEND CMAKE_CXX_FLAGS " /Zc:__cpluscplus /MP")
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

find_package(
  Qt5
  COMPONENTS Widgets Svg
  REQUIRED)

option(BUILD_DEMO "Build demo" ON)

# main dir
set(INC_DIR include)
set(SRC_DIR src)

set(GLOBALE_FILES ${INC_DIR}/roler/roler_global.h)

# modules dir
set(INC_WIDGETS ${INC_DIR}/roler/widgets)
set(SRC_WIDGETS ${SRC_DIR}/widgets)
set(WIDGETS_FILES
    ${INC_WIDGETS}/passwordlineedit.h
    ${SRC_WIDGETS}/passwordlineedit.cpp
    ${INC_WIDGETS}/tagwidget.h
    ${SRC_WIDGETS}/tagwidget.cpp
    ${INC_WIDGETS}/synccheckbox.h
    ${SRC_WIDGETS}/synccheckbox.cpp
    ${INC_WIDGETS}/paginationwidget.h
    ${SRC_WIDGETS}/paginationwidget.cpp
    ${INC_WIDGETS}/lengthhintlineedit.h
    ${SRC_WIDGETS}/lengthhintlineedit.cpp
    ${INC_WIDGETS}/autoclosemessagebox.h
    ${SRC_WIDGETS}/autoclosemessagebox.cpp)

set(SOURCE_FILES
  ${GLOBALE_FILES} 
  ${WIDGETS_FILES}
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Qt::Widgets Qt::Svg)

target_compile_definitions(${PROJECT_NAME} PRIVATE ROLER_LIBRARY)

target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

if(BUILD_DEMO)
  message(STATUS "build demo")
  add_subdirectory(demo)
endif()
