# CMake version
cmake_minimum_required(VERSION 3.5)
# Project name
project(TcpServer)

# ???
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# C++ Standart
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QT stuff
find_package(Qt5 COMPONENTS Core Network REQUIRED)

# ???
include_directories(
    .
)

# ??? src/* ???
set (SRCS src/main.cpp src/tcpserver.cpp src/tcpserver.h src/functions.cpp src/functions.h)

# ???
add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

# ???
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network)
