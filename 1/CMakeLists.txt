cmake_minimum_required(VERSION 3.10)

# Устанавливаем компилятор до вызова project
set(CMAKE_CXX_COMPILER clang++)
project(lab1)

# Настройка стандарта
set(CMAKE_CXX_STANDARD 23)

# Источники
file(GLOB SOURCES main.cpp detail.cpp)

find_package(GTest CONFIG REQUIRED)

# Основной исполняемый файл для стандартной сборки
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wextra -Wall -Werror)

# Цель для отладочной сборки
add_executable(debug_target ${SOURCES})
set_target_properties(debug_target PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_debug)
target_compile_options(debug_target PRIVATE -g)

add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target debug_target
    COMMENT "Building in debug mode"
)

# Цель для AddressSanitizer
add_executable(asan_target ${SOURCES})
target_compile_options(asan_target PRIVATE -g "-fsanitize=address" "-fsanitize=undefined" -Wextra -Wall)
target_link_options(asan_target PRIVATE "-fsanitize=address" "-fsanitize=undefined")
set_target_properties(asan_target PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_asan)

add_custom_target(asan
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target asan_target
    COMMENT "Building with AddressSanitizer"
)

# Цель для MemorySanitizer
add_executable(msan_target ${SOURCES})
set_target_properties(msan_target PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_msan)
target_compile_options(msan_target PRIVATE -g -Wextra -Wall "-fsanitize=memory" "-fsanitize=undefined")
target_link_options(msan_target PRIVATE "-fsanitize=memory" "-fsanitize=undefined")

add_custom_target(msan
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target msan_target
    COMMENT "Building with MemorySanitizer"
)

# Цель для сборки с gprof
add_executable(gprof_target ${SOURCES})
set_target_properties(gprof_target PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_gprof)
target_compile_options(gprof_target PRIVATE -pg)

add_custom_target(gprof
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target gprof_target
    COMMENT "Building with gprof"
)

# Запуск статического анализа
add_custom_target(static
    COMMAND clang++ --analyze -Xanalyzer -analyzer-output=html ${SOURCES}
    COMMENT "Running static analysis"
)

# Запуск Valgrind
add_custom_target(valgrind
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target debug_target
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./${PROJECT_NAME}_debug
    COMMENT "Running Valgrind"
)

# Сбор покрытия
add_executable(coverage_target ${SOURCES})
set_target_properties(coverage_target PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_cov)
target_link_options(coverage_target PRIVATE -fprofile-instr-generate -fcoverage-mapping)
target_compile_options(coverage_target PRIVATE -fprofile-instr-generate -fcoverage-mapping)

add_custom_target(cov
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target coverage_target
    COMMAND ./${PROJECT_NAME}_cov
    COMMAND llvm-profdata merge -sparse default.profraw -o foo.profdata
    COMMAND llvm-cov show ${PROJECT_NAME}_cov -instr-profile=foo.profdata
    COMMAND llvm-cov report ${PROJECT_NAME}_cov -instr-profile=foo.profdata
    COMMAND llvm-cov show ${PROJECT_NAME}_cov -instr-profile=foo.profdata -format=html -output-dir=report_coverage
    COMMAND rm foo.profdata default.profraw
    COMMENT "Building with coverage"
)


# Очистка
add_custom_target(clear
    COMMAND rm -rf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}*
    COMMENT "Cleaning build"
)
