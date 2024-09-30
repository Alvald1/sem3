file(GLOB TESTING ../signal.cpp unit_tests.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

# Запуск тестов и сбор покрытия
add_executable(test_target ${TESTING})
set_target_properties(test_target PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_test)
target_link_options(test_target PRIVATE -fprofile-instr-generate -fcoverage-mapping -g)
target_compile_options(test_target PRIVATE -fprofile-instr-generate -fcoverage-mapping -g)
target_link_libraries(test_target ${GTEST_LIBRARIES} gtest_main pthread)

add_custom_target(cov)

add_custom_command(TARGET cov
    COMMAND test_target
    COMMAND llvm-profdata merge -sparse default.profraw -o foo.profdata
    COMMAND llvm-cov report ${PROJECT_NAME}_test -instr-profile=foo.profdata
    COMMAND llvm-cov show ${PROJECT_NAME}_test -instr-profile=foo.profdata -format=html -output-dir=report_coverage
    COMMAND rm foo.profdata default.profraw
    COMMENT "Building with coverage"
) 



add_test(NAME test COMMAND test_target)