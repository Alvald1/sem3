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
TEST(complex_signal_operator, square_brackets_valid_position) {
    Complex_Signal complex_signal("001110");
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 1);
    EXPECT_EQ(complex_signal[6], 0);
}

// Test operator square brackets with invalid positions
TEST(complex_signal_operator, square_brackets_invalid_position) {
    Complex_Signal complex_signal("001110");
    EXPECT_THROW(complex_signal[0], std::invalid_argument);
    EXPECT_THROW(complex_signal[7], std::invalid_argument);
}

// Test the copy constructor
TEST(complex_signal_constructor, copy) {
    Complex_Signal complex_signal("001110");
    Complex_Signal complex_signal_copy(complex_signal);
    EXPECT_EQ(complex_signal_copy[1], 0);
    EXPECT_EQ(complex_signal_copy[2], 0);
    EXPECT_EQ(complex_signal_copy[3], 1);
    EXPECT_EQ(complex_signal_copy[4], 1);
    EXPECT_EQ(complex_signal_copy[5], 1);
    EXPECT_EQ(complex_signal_copy[6], 0);
}

// Test the move constructor
TEST(complex_signal_constructor, move) {
    Complex_Signal complex_signal("001110");
    Complex_Signal complex_signal_move(std::move(complex_signal));
    EXPECT_EQ(complex_signal_move[1], 0);
    EXPECT_EQ(complex_signal_move[2], 0);
    EXPECT_EQ(complex_signal_move[3], 1);
    EXPECT_EQ(complex_signal_move[4], 1);
    EXPECT_EQ(complex_signal_move[5], 1);
    EXPECT_EQ(complex_signal_move[6], 0);
}

// Test the copy assignment operator
TEST(complex_signal_operator, copy) {
    Complex_Signal complex_signal("001110");
    Complex_Signal complex_signal_copy;
    complex_signal_copy = complex_signal;
    EXPECT_EQ(complex_signal_copy[1], 0);
    EXPECT_EQ(complex_signal_copy[2], 0);
    EXPECT_EQ(complex_signal_copy[3], 1);
    EXPECT_EQ(complex_signal_copy[4], 1);
    EXPECT_EQ(complex_signal_copy[5], 1);
    EXPECT_EQ(complex_signal_copy[6], 0);
}

// Test the copy assignment operator
TEST(complex_signal_operator, copy_yourself) {
    Complex_Signal complex_signal("001110");
    complex_signal = complex_signal;
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 1);
    EXPECT_EQ(complex_signal[6], 0);
}

// Test the move assignment operator
TEST(complex_signal_operator, move) {
    Complex_Signal complex_signal("001110");
    Complex_Signal complex_signal_move;
    complex_signal_move = std::move(complex_signal);
    EXPECT_EQ(complex_signal_move[1], 0);
    EXPECT_EQ(complex_signal_move[2], 0);
    EXPECT_EQ(complex_signal_move[3], 1);
    EXPECT_EQ(complex_signal_move[4], 1);
    EXPECT_EQ(complex_signal_move[5], 1);
    EXPECT_EQ(complex_signal_move[6], 0);
}

// Test the inversion
TEST(complex_signal_inversion, inversion) {
    Complex_Signal complex_signal("001110");
    complex_signal.inverstion();
    EXPECT_EQ(complex_signal[1], 1);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 0);
    EXPECT_EQ(complex_signal[6], 1);
}

// Test the inversion operator
TEST(complex_signal_operator, inversion) {
    Complex_Signal complex_signal("001110");
    ~complex_signal;
    EXPECT_EQ(complex_signal[1], 1);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 0);
    EXPECT_EQ(complex_signal[6], 1);
}

// Test the addition operator
TEST(complex_signal_operator, addition_valid) {
    Complex_Signal complex_signal("001");
    Complex_Signal complex_signal2("010");
    complex_signal += complex_signal2;
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 1);
    EXPECT_EQ(complex_signal[6], 0);
}

// Test the addition operator yourself
TEST(complex_signal_operator, addition_yourself) {
    Complex_Signal complex_signal("001");
    complex_signal += complex_signal;
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 0);
    EXPECT_EQ(complex_signal[6], 1);
}

// Test the addition operator sequentially
TEST(complex_signal_operator, addition_sequentially) {
    Complex_Signal complex_signal("001");
    complex_signal += complex_signal += complex_signal;
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 0);
    EXPECT_EQ(complex_signal[6], 1);
    EXPECT_EQ(complex_signal[7], 0);
    EXPECT_EQ(complex_signal[8], 0);
    EXPECT_EQ(complex_signal[9], 1);
}