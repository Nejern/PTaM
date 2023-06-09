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

# Генерация compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Опции компиляции
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic -Werror -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Wpedantic -pthread")

# Сбор исходных файлов
file(GLOB SOURCES
    ${SRC_DIR}/*.cpp
)

# Исключаем из сборки исходный файл с тестами
list(REMOVE_ITEM SOURCES ${SRC_DIR}/test.cpp)

# Поиск необходимых компонентов Qt
find_package(Qt5 REQUIRED COMPONENTS Core Network Sql Test)
set(CMAKE_AUTOMOC ON)

# Проверка версии Qt
if(Qt5_VERSION VERSION_LESS "5.12")
  message(FATAL_ERROR "Qt5 version must be at least 5.12")
endif()

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network Qt5::Sql)
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})

# Добавляем исполняемый файл для тестов
file(GLOB TEST_SOURCES 
    ${SRC_DIR}/*.cpp
)
# Исключаем из сборки исходный файл main.cpp
list(REMOVE_ITEM TEST_SOURCES ${SRC_DIR}/main.cpp)

add_executable(${PROJECT_NAME}Tests ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}Tests PRIVATE Qt5::Core Qt5::Network Qt5::Sql Qt5::Test)
target_include_directories(${PROJECT_NAME}Tests PRIVATE ${INC_DIR})
