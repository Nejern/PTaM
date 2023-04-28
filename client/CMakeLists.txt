cmake_minimum_required(VERSION 3.15)

# Название проекта и версия
project(Client VERSION 1.0 LANGUAGES CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Генерация compile_commands.json для clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Настройки компиляции и линковки
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic -Werror -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Wpedantic -pthread")

# Настройки директорий
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(UI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ui)
set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Настройки для исполняемого файла
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Поиск и линковка Qt библиотек
find_package(Qt5 REQUIRED COMPONENTS UiTools Widgets Network)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_DIR})
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

# Сбор исходных файлов
file(GLOB SOURCES
    ${SRC_DIR}/*.cpp
    ${INC_DIR}/*.h
    ${UI_DIR}/*.ui
    ${RES_DIR}/*.qrc
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES})

# Линковка библиотек Qt и папки include
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network)
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})
