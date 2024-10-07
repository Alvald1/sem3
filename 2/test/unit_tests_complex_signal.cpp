#include <limits>

#include <gtest/gtest.h>
#include "../complex_signal/complex_signal.hpp"

// Test the constructor level and duration
TEST(complex_signal_constructor, level_duration) {
    Complex_Signal complex_signal(1, 10);
    EXPECT_EQ(complex_signal[1], 1);
    EXPECT_EQ(complex_signal[10], 1);
}

// Test the constructor with a valid binary string
TEST(complex_signal_constructor, valid_string) {
    Complex_Signal complex_signal("001110");
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 1);
    EXPECT_EQ(complex_signal[6], 0);
}

// Test the constructor with a valid binary string 2
TEST(complex_signal_constructor, valid_string_2) {
    Complex_Signal complex_signal("001a110");
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_THROW(complex_signal[4], std::invalid_argument);
}

// Test the constructor with an invalid binary string
TEST(complex_signal_constructor, invalid_string_1) {
    EXPECT_THROW(Complex_Signal complex_signal("a001110"), std::invalid_argument);
}

// Test the constructor with empty binary string
TEST(complex_signal_constructor, invalid_string_2) {
    EXPECT_THROW(Complex_Signal complex_signal(""), std::invalid_argument);
}

// Test operator square brackets with valid positions
TEST(complex_signal_operator_square_brackets, valid_position) {
    Complex_Signal complex_signal("001110");
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 1);
    EXPECT_EQ(complex_signal[6], 0);
}

TEST(complex_signal_operator_square_brackets, invalid_position) {
    Complex_Signal complex_signal("001110");
    EXPECT_THROW(complex_signal[0], std::invalid_argument);
    EXPECT_THROW(complex_signal[7], std::invalid_argument);
}