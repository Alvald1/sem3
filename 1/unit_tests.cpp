/**
 * @file unit_tests.cpp
 * @brief Unit tests for the Detail_info class using Google Test framework.
 */

#include <gtest/gtest.h>
#include <string>
#include "detail.hpp"

using std::string;

/**
 * @test DetailInfoTest.EncodeFunctionWorks
 * @brief Tests the encode() function without parameters.
 */
TEST(DetailInfoTest, EncodeFunctionWorks) {
    Detail_info detail("002", "PartA", 50);
    string encoded = detail.encode();

    EXPECT_EQ(encoded, "{'id':'002','name':'PartA','count':50}");
}

/**
 * @test DetailInfoTest.EncodeWithParametersWorks
 * @brief Tests the encode() function with parameters.
 */
TEST(DetailInfoTest, EncodeWithParametersWorks) {
    Detail_info detail;
    string encoded = detail.encode("003", "PartB", 25);

    EXPECT_EQ(encoded, "{'id':'003','name':'PartB','count':25}");
}

/**
 * @test DetailInfoTest.DecodeFunctionWorks
 * @brief Tests the decode() function with valid input std::string.
 */
TEST(DetailInfoTest, DecodeFunctionWorks) {
    Detail_info detail;
    string input = "{'id':'004','name':'PartC','count':75}";

    detail.decode(input);

    EXPECT_EQ(detail.encode(), "{'id':'004','name':'PartC','count':75}");
}

/**
 * @test DetailInfoTest.DecodeFunctionWorks2
 * @brief Tests the decode() function with valid input const char*.
 */
TEST(DetailInfoTest, DecodeFunctionWorks2) {
    Detail_info detail;
    const char* input = "{'id':'004','name':'PartC','count':75}";

    detail.decode(input);

    EXPECT_EQ(detail.encode(), "{'id':'004','name':'PartC','count':75}");
}

/**
 * @test DetailInfoTest.DecodeFunctionWorks3
 * @brief Tests the decode() function with valid input const char* and size.
 */
TEST(DetailInfoTest, DecodeFunctionWorks3) {
    Detail_info detail;
    const char* tmp = "{'id':'004','name':'PartC','count':75}";
    std::size_t size = strlen(tmp);
    char* input = new char[size];
    std::copy(tmp, tmp + size, input);

    detail.decode(input, size);

    delete[] input;

    EXPECT_EQ(detail.encode(), "{'id':'004','name':'PartC','count':75}");
}

/**
 * @test DetailInfoTest.DecodeFunctionInvalidInput
 * @brief Tests the decode() function with invalid input std::string.
 * @throws errors
 */
TEST(DetailInfoTest, DecodeFunctionInvalidInput) {
    Detail_info detail;
    string invalidInput = "{'invalid':'004','name':'PartC','count':'seventy-five'}";

    EXPECT_THROW(detail.decode(invalidInput), errors);
}

/**
 * @test DetailInfoTest.DecodeFunctionInvalidInput2
 * @brief Tests the decode() function with invalid input const char*.
 * @throws errors
 */
TEST(DetailInfoTest, DecodeFunctionInvalidInput2) {
    Detail_info detail;
    const char* invalidInput = "{'id':'004','name':'PartC','count':'seventy-five'}";

    EXPECT_THROW(detail.decode(invalidInput), errors);
}

/**
 * @test DetailInfoTest.DecodeFunctionInvalidInput3
 * @brief Tests the decode() function with invalid input const char* and size.
 * @throws errors
 */
TEST(DetailInfoTest, DecodeFunctionInvalidInput3) {
    Detail_info detail;
    const char* tmp = "{'id':'004','name':'PartC','count':'seventy-five'}";
    std::size_t size = strlen(tmp);
    char* invalidInput = new char[size];
    std::copy(tmp, tmp + size, invalidInput);

    EXPECT_THROW(detail.decode(invalidInput), errors);

    delete[] invalidInput;
}

/**
 * @test DetailInfoTest.DefaultConstructorWorks
 * @brief Tests the default constructor.
 */
TEST(DetailInfoTest, DefaultConstructorWorks) {
    Detail_info detail;

    EXPECT_EQ(detail.encode(), "{'id':'','name':'','count':0}");
}

/**
 * @test DetailInfoTest.ParameterizedConstructorWorks
 * @brief Tests the constructor with parameters.
 */
TEST(DetailInfoTest, ParameterizedConstructorWorks) {
    Detail_info detail("005", "PartD", 150);

    EXPECT_EQ(detail.encode(), "{'id':'005','name':'PartD','count':150}");
}

/**
 * @test DetailInfoTest.ConstructorWithEncodedStringWorks
 * @brief Tests the constructor with encoded string input.
 */
TEST(DetailInfoTest, ConstructorWithEncodedStringWorks) {
    string input = "{'id':'006','name':'PartE','count':30}";
    Detail_info detail(input);

    EXPECT_EQ(detail.encode(), "{'id':'006','name':'PartE','count':30}");
}

/**
 * @test DetailInfoTest.PrintFunctionWorks
 * @brief Tests the print() function.
 */
TEST(DetailInfoTest, PrintFunctionWorks) {
    Detail_info detail("007", "PartF", 200);
    testing::internal::CaptureStdout();
    detail.print();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "id: 007\nname: PartF\ncount: 200\n");
}
