cmake_minimum_required(VERSION 3.5)

set(PROJECT_SOURCES main.cpp mainwindow.cpp mainwindow.h mainwindow.ui)

include_directories(../include)

add_custom_target(copy_resource ALL
  VERBATIM
  COMMAND ${CMAKE_COMMAND} -E make_directory "resource"
  COMMAND ${CMAKE_COMMAND} -E 
    copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resource"
    "resource"
)

add_executable(demo ${PROJECT_SOURCES})

target_link_libraries(
  demo
  PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
  PRIVATE roler-qtlib)
