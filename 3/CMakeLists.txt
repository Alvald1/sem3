cmake_minimum_required(VERSION 3.13)

# Enable parallel build
include(ProcessorCount)
ProcessorCount(N)
message(STATUS "Number of available CPU cores: ${N}")
if(NOT N EQUAL 0)
    set(N_JOBS ${N} CACHE STRING "Number of parallel jobs")
    # Enable parallel build globally
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N_JOBS})
    set(CMAKE_PARALLEL_LEVEL ${N_JOBS})
else()
    set(N_JOBS 2 CACHE STRING "Number of parallel jobs")
endif()

# Проверка наличия инструментов
find_program(CLANG_PP "clang++")
find_program(GPP "g++")

if(NOT CLANG_PP AND NOT GPP)
    message(FATAL_ERROR "Neither clang++ nor g++ found!")
endif()

# Выбор компилятора (clang++ по умолчанию)
if(CLANG_PP)
    set(CMAKE_CXX_COMPILER clang++)
else()
    set(CMAKE_CXX_COMPILER g++)
endif()

find_program(VALGRIND "valgrind")
if(NOT VALGRIND)
    message(FATAL_ERROR "valgrind not found!")
endif()

# Установка компилятора
project(lab3)

# Set output directories for all targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Общие настройки
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Добавляем пути для поиска заголовочных файлов
include_directories(${CMAKE_SOURCE_DIR}/src)

# Общие флаги компиляции
set(COMMON_COMPILE_FLAGS -Wall -Werror -Wextra)
set(DEBUG_FLAGS -g -O0)
set(ASAN_FLAGS -fsanitize=address -fsanitize=undefined)
set(MSAN_FLAGS -fsanitize=memory -fsanitize=undefined)

# Find ncurses package
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Find RapidJSON
find_package(RapidJSON REQUIRED)
include_directories(${RAPIDJSON_INCLUDE_DIRS})

# Делегируем в src, test, doc
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)


# Очистка артефактов анализа
add_custom_target(clean_analysis
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/analyzer-output
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/html
    COMMENT "Cleaning analysis artifacts"
)