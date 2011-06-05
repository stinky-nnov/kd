project(kd)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(kd_SRCS logger.cpp kd.cpp main.cpp)
qt4_automoc(${kd_SRCS})
add_executable(kd ${kd_SRCS})
target_link_libraries(kd ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
