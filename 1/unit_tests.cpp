#include <gtest/gtest.h>
#include <string>
#include "detail.hpp"

using std::string;

// Test the encode() function without parameters
TEST(DetailInfoTest, EncodeFunctionWorks) {
    Detail_info detail("002", "PartA", 50);
    string encoded = detail.encode();

    EXPECT_EQ(encoded, "{'id':'002','name':'PartA','count':50}");
}

// Test the encode() function with parameters
TEST(DetailInfoTest, EncodeWithParametersWorks) {
    Detail_info detail;
    string encoded = detail.encode("003", "PartB", 25);

    EXPECT_EQ(encoded, "{'id':'003','name':'PartB','count':25}");
}

// Test the decode() function with valid input std::string
TEST(DetailInfoTest, DecodeFunctionWorks) {
    Detail_info detail;
    string input = "{'id':'004','name':'PartC','count':75}";

    detail.decode(input);

    EXPECT_EQ(detail.encode(), "{'id':'004','name':'PartC','count':75}");
}

// Test the decode() function with valid input const char*
TEST(DetailInfoTest, DecodeFunctionWorks2) {
    Detail_info detail;
    const char* input = "{'id':'004','name':'PartC','count':75}";

    detail.decode(input);

    EXPECT_EQ(detail.encode(), "{'id':'004','name':'PartC','count':75}");
}

// Test the decode() function with valid input const char* + size
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

// Test the decode() function with invalid input std::string
TEST(DetailInfoTest, DecodeFunctionInvalidInput) {
    Detail_info detail;
    string invalidInput = "{'invalid':'004','name':'PartC','count':'seventy-five'}";

    EXPECT_THROW(detail.decode(invalidInput), errors);
}

// Test the decode() function with invalid input const char*

TEST(DetailInfoTest, DecodeFunctionInvalidInput2) {
    Detail_info detail;
    const char* invalidInput = "{'id':'004','name':'PartC','count':'seventy-five'}";

    EXPECT_THROW(detail.decode(invalidInput), errors);
}

// Test the decode() function with invalid input const char* + size

TEST(DetailInfoTest, DecodeFunctionInvalidInput3) {
    Detail_info detail;
    const char* tmp = "{'id':'004','name':'PartC','count':'seventy-five'}";
    std::size_t size = strlen(tmp);
    char* invalidInput = new char[size];
    std::copy(tmp, tmp + size, invalidInput);

    EXPECT_THROW(detail.decode(invalidInput), errors);

    delete[] invalidInput;
}

// Test the default constructor
TEST(DetailInfoTest, DefaultConstructorWorks) {
    Detail_info detail;

    EXPECT_EQ(detail.encode(), "{'id':'','name':'','count':0}");
}

// Test the constructor with parameters
TEST(DetailInfoTest, ParameterizedConstructorWorks) {
    Detail_info detail("005", "PartD", 150);

    EXPECT_EQ(detail.encode(), "{'id':'005','name':'PartD','count':150}");
}

// Test the constructor with encoded string
TEST(DetailInfoTest, ConstructorWithEncodedStringWorks) {
    string input = "{'id':'006','name':'PartE','count':30}";
    Detail_info detail(input);

    EXPECT_EQ(detail.encode(), "{'id':'006','name':'PartE','count':30}");
}

// Test the print function (for completeness)
TEST(DetailInfoTest, PrintFunctionWorks) {
    Detail_info detail("007", "PartF", 200);
    testing::internal::CaptureStdout();
    detail.print();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "id: 007\nname: PartF\ncount: 200\n");
}
