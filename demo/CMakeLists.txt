cmake_minimum_required(VERSION 3.5)

set(PROJECT_SOURCES main.cpp mainwindow.cpp mainwindow.h mainwindow.ui)

add_executable(demo ${PROJECT_SOURCES})

target_link_libraries(
  demo
  PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
  PRIVATE roler-qtlib)

set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})