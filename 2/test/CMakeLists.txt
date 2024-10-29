
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

file(GLOB TEST unit_tests_signal.cpp unit_tests_allocator.cpp unit_tests_complex_signal.cpp)

set(CXXFLAGS -fprofile-instr-generate -fcoverage-mapping -g -O0)
set(LDFLAGS -fprofile-instr-generate)

# Запуск тестов и сбор покрытия
add_executable(test_target ${TEST})
set_target_properties(test_target PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_test)
target_compile_options(test_target PRIVATE ${CXXFLAGS})
target_link_options(test_target PRIVATE ${LDFLAGS})
target_link_libraries(test_target ${GTEST_LIBRARIES} gtest_main pthread)

add_custom_target(cov)

add_custom_command(TARGET cov
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_target
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJECT_NAME}_test
    COMMAND llvm-profdata merge -sparse default.profraw -o foo.profdata
    COMMAND llvm-cov report ${PROJECT_NAME}_test -instr-profile=foo.profdata
    COMMAND llvm-cov show ${PROJECT_NAME}_test -instr-profile=foo.profdata -format=html -output-dir=report_coverage
    COMMAND rm foo.profdata default.profraw
    COMMENT "Building with coverage"
) 


add_test(NAME test COMMAND test_target)