cmake_minimum_required(VERSION 3.13)

# Устанавливаем компилятор до вызова project
set(CMAKE_CXX_COMPILER clang++)
project(lab2)

# Настройка стандарта
set(CMAKE_CXX_STANDARD 23)

# Источники
file(GLOB ALL allocator/allocator.cpp signal/signal.cpp complex_signal/complex_signal.cpp)

file(GLOB MAIN main.cpp)

# Цель для основной сборки
add_executable(${PROJECT_NAME} ${MAIN})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra)

# Цель для отладочной сборки
add_executable(debug ${MAIN})
set_target_properties(debug PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_debug)
target_compile_options(debug PRIVATE -g -O0)

# Цель для AddressSanitizer
add_executable(asan ${MAIN})
set_target_properties(asan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_asan)
target_compile_options(asan PRIVATE -g "-fsanitize=address" "-fsanitize=undefined" -Wextra -Wall -Werror)
target_link_options(asan PRIVATE -g "-fsanitize=address" "-fsanitize=undefined" -Wextra -Wall -Werror)


# Цель для MemorySanitizer
add_executable(msan ${MAIN})
set_target_properties(msan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_msan)
target_compile_options(msan PRIVATE -g "-fsanitize=memory" "-fsanitize=undefined" -Wextra -Wall -Werror)
target_link_options(msan PRIVATE -g "-fsanitize=memory" "-fsanitize=undefined" -Wextra -Wall -Werror)


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
add_subdirectory(allocator)
add_subdirectory(signal)
add_subdirectory(complex_signal)