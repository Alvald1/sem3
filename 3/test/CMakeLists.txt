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

# Use parent's N_JOBS for parallel execution
if(N_JOBS)
    set(CTEST_BUILD_FLAGS -j${N_JOBS})
    set(CTEST_PARALLEL_LEVEL ${N_JOBS})
endif()

# Add custom command for coverage with detailed reporting
add_custom_target(cov
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_target --parallel ${N_JOBS}
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PROJECT_NAME}_test
    COMMAND llvm-profdata merge -sparse default.profraw -o foo.profdata
    # Text summary
    COMMAND llvm-cov report ${PROJECT_NAME}_test 
            -instr-profile=foo.profdata 
            --show-branch-summary
            ${SOURCES}
            -stats
    # Detailed HTML report
    COMMAND llvm-cov show ${PROJECT_NAME}_test 
            -instr-profile=foo.profdata 
            -show-branch-summary
            -show-branches=count
            -show-expansions
            -show-line-counts-or-regions 
            -show-instantiation-summary
            -show-regions
            -show-line-counts
            -use-color
            -Xdemangler=c++filt
            -format=html 
            -output-dir=report_coverage 
            ${SOURCES}
    COMMAND rm foo.profdata default.profraw
    COMMENT "Building with detailed coverage reports"
)

# Add test with parallel configuration
add_test(NAME test COMMAND test_target)
set_tests_properties(test 
    PROPERTIES 
    PROCESSORS ${N_JOBS}
    ENVIRONMENT CMAKE_BUILD_PARALLEL_LEVEL=${N_JOBS}
)

# Force parallel test execution
set(CTEST_PARALLEL_LEVEL ${N_JOBS})
set(CMAKE_CTEST_COMMAND ctest -j${N_JOBS})