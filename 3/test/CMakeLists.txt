
include(FetchContent)

# Fetch googletest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Find required programs
find_program(VALGRIND "valgrind")
if(NOT VALGRIND)
    message(FATAL_ERROR "valgrind not found! Please install valgrind.")
endif()

find_program(LLVM_COV "llvm-cov")
if(NOT LLVM_COV)
    message(FATAL_ERROR "llvm-cov not found! Please install llvm-cov.")
endif()

enable_testing()

# Find all test files
file(GLOB TEST unit_tests_*.cpp)

# Set compile and link flags
set(CXXFLAGS -fprofile-instr-generate -fcoverage-mapping -g -O0)
set(LDFLAGS -fprofile-instr-generate)

# Add test executable
add_executable(test_target ${TEST})
set_target_properties(test_target PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_test)
target_compile_options(test_target PRIVATE ${CXXFLAGS})
target_link_options(test_target PRIVATE ${LDFLAGS})
target_link_libraries(test_target GTest::gtest GTest::gtest_main pthread)

# Add custom command for coverage
add_custom_target(cov
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_target
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJECT_NAME}_test
    COMMAND llvm-profdata merge -sparse default.profraw -o foo.profdata
    COMMAND llvm-cov report ${PROJECT_NAME}_test -instr-profile=foo.profdata
    COMMAND llvm-cov show ${PROJECT_NAME}_test -instr-profile=foo.profdata -format=html -output-dir=report_coverage
    COMMAND rm foo.profdata default.profraw
    COMMENT "Building with coverage"
)

# Add test
add_test(NAME test COMMAND test_target)