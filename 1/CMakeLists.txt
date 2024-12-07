cmake_minimum_required(VERSION 3.10)

# Устанавливаем компилятор до вызова project
set(CMAKE_CXX_COMPILER clang++)
project(lab1)

# Настройка стандарта
set(CMAKE_CXX_STANDARD 23)

# Источники
file(GLOB SOURCES main.cpp detail.cpp)

file(GLOB ALL *.cpp)


# Цель для основной сборки
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra)

# Цель для отладочной сборки
add_executable(debug  ${SOURCES})
set_target_properties(debug PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_debug)
target_compile_options(debug PRIVATE -g)

# Цель для AddressSanitizer
add_executable(asan  ${SOURCES})
target_compile_options(asan PRIVATE -g "-fsanitize=address" "-fsanitize=undefined" -Wextra -Wall -Werror)
target_link_options(asan PRIVATE "-fsanitize=address" "-fsanitize=undefined")
set_target_properties(asan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_asan)


# Цель для MemorySanitizer
add_executable(msan  ${SOURCES})
set_target_properties(msan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_msan)
target_compile_options(msan PRIVATE -g -Wextra -Wall -Werror "-fsanitize=memory" "-fsanitize=undefined")
target_link_options(msan PRIVATE "-fsanitize=memory" "-fsanitize=undefined")


# Запуск Valgrind
add_custom_target(valgrind
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target debug
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./${PROJECT_NAME}_debug
    COMMENT "Running Valgrind"
)

# Запуск статического анализа
add_custom_target(static
    COMMAND clang++ -std=c++2b --analyze -Xanalyzer -analyzer-output=html  ${ALL}
    COMMENT "Running static analysis"
)

add_subdirectory(test)