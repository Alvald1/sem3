cmake_minimum_required(VERSION 3.13)

# Проверка наличия инструментов
find_program(CLANG_PP "clang++")
if(NOT CLANG_PP)
    message(FATAL_ERROR "clang++ not found!")
endif()

find_program(VALGRIND "valgrind")
if(NOT VALGRIND)
    message(FATAL_ERROR "valgrind not found!")
endif()

# Установка компилятора
set(CMAKE_CXX_COMPILER clang++)
project(lab2)

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
file(GLOB_RECURSE SOURCES 
    ${SRC_DIR}/allocator/*.cpp
    ${SRC_DIR}/signal/*.cpp
    ${SRC_DIR}/complex_signal/*.cpp
)
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
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target debug
    COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all 
            --track-origins=yes --verbose ./${PROJECT_NAME}_debug
    COMMENT "Running Valgrind"
)

# Статический анализ
add_custom_target(static
    COMMAND ${CLANG_PP} -std=c++2b --analyze -Xanalyzer -analyzer-output=html ${SOURCES}
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
add_subdirectory(src)
add_subdirectory(doc)