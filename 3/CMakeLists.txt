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

# Общие настройки
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Общие флаги компиляции
set(COMMON_COMPILE_FLAGS -Wall -Werror -Wextra)
set(DEBUG_FLAGS -g -O0)
set(ASAN_FLAGS -fsanitize=address -fsanitize=undefined)
set(MSAN_FLAGS -fsanitize=memory -fsanitize=undefined)

# Организация исходников
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES ${SRC_DIR}/**/*.cpp ${SRC_DIR}/**/*.hpp)
set(MAIN_SOURCE ${SRC_DIR}/main.cpp)

# Основная цель
add_executable(${PROJECT_NAME} ${MAIN_SOURCE} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_FLAGS})

# Отладочная сборка
add_executable(debug ${MAIN_SOURCE} ${SOURCES})
target_compile_options(debug PRIVATE ${COMMON_COMPILE_FLAGS} ${DEBUG_FLAGS})
set_target_properties(debug PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_debug)

# AddressSanitizer
add_executable(asan ${MAIN_SOURCE} ${SOURCES})
target_compile_options(asan PRIVATE ${COMMON_COMPILE_FLAGS} ${DEBUG_FLAGS} ${ASAN_FLAGS})
target_link_options(asan PRIVATE ${ASAN_FLAGS})
set_target_properties(asan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_asan)

# MemorySanitizer
add_executable(msan ${MAIN_SOURCE} ${SOURCES})
target_compile_options(msan PRIVATE ${COMMON_COMPILE_FLAGS} ${DEBUG_FLAGS} ${MSAN_FLAGS})
target_link_options(msan PRIVATE ${MSAN_FLAGS})
set_target_properties(msan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_msan)

# Valgrind
add_custom_target(valgrind
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target debug -j${N_JOBS}
    COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all 
            --track-origins=yes --verbose ./${PROJECT_NAME}_debug
    COMMENT "Running Valgrind"
)

# Статический анализ
add_custom_target(static
    COMMAND ${CLANG_PP} -std=c++2b --analyze -Xanalyzer -analyzer-output=html ${SOURCES} -j${N_JOBS}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running static analysis"
)

# Очистка артефактов анализа
add_custom_target(clean_analysis
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/analyzer-output
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/html
    COMMENT "Cleaning analysis artifacts"
)

add_subdirectory(test)
add_subdirectory(doc)
add_subdirectory(src)