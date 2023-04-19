# Версия CMake
cmake_minimum_required(VERSION 3.15)

# Название проекта
project(TcpServer VERSION 1.0)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройки директорий
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Настройки для исполняемого файла
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Опции компиляции
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic -Werror -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Wpedantic -pthread")

# Сбор исходных файлов
set(SRCS
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/tcpserver.cpp
    ${SRC_DIR}/functions.cpp
    ${SRC_DIR}/mydb.cpp
)

# Поиск необходимых компонентов Qt
find_package(Qt5 REQUIRED COMPONENTS Core Network Sql)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Проверка версии Qt
if(Qt5_VERSION VERSION_LESS "5.12")
  message(FATAL_ERROR "Qt5 version must be at least 5.12")
endif()

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SRCS})

# Линковка библиотек Qt и папки include
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network Qt5::Sql)
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})

