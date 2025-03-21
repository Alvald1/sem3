#include <limits>

#include <gtest/gtest.h>
#include "../complex_signal/complex_signal.hpp"

// Test the constructor level and duration
TEST(complex_signal_constructor, level_duration) {
    Complex_Signal complex_signal(1, 10);
    EXPECT_EQ(complex_signal[0], 1);
    EXPECT_EQ(complex_signal[9], 1);
}

// Test the constructor with a valid binary string
TEST(complex_signal_constructor, valid_string) {
    Complex_Signal complex_signal("001110");
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 0);
}

// Test the constructor with a valid binary string 2
TEST(complex_signal_constructor, valid_string_2) {
    Complex_Signal complex_signal("001a110");
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_THROW(complex_signal[3], std::out_of_range);
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
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 0);
}

// Test operator square brackets with invalid positions
TEST(complex_signal_operator, square_brackets_invalid_position) {
    Complex_Signal complex_signal("001110"), complex_signal_empty;
    EXPECT_THROW(complex_signal_empty[2], std::out_of_range);
    EXPECT_THROW(complex_signal[-1], std::out_of_range);
    EXPECT_THROW(complex_signal[10], std::out_of_range);
}

// Test the copy constructor
TEST(complex_signal_constructor, copy) {
    Complex_Signal complex_signal("001110");
    Complex_Signal complex_signal_copy(complex_signal);
    EXPECT_EQ(complex_signal_copy[0], 0);
    EXPECT_EQ(complex_signal_copy[1], 0);
    EXPECT_EQ(complex_signal_copy[2], 1);
    EXPECT_EQ(complex_signal_copy[3], 1);
    EXPECT_EQ(complex_signal_copy[4], 1);
    EXPECT_EQ(complex_signal_copy[5], 0);
}

// Test the move constructor
TEST(complex_signal_constructor, move) {
    Complex_Signal complex_signal("001110");
    Complex_Signal complex_signal_move(std::move(complex_signal));
    EXPECT_EQ(complex_signal_move[0], 0);
    EXPECT_EQ(complex_signal_move[1], 0);
    EXPECT_EQ(complex_signal_move[2], 1);
    EXPECT_EQ(complex_signal_move[3], 1);
    EXPECT_EQ(complex_signal_move[4], 1);
    EXPECT_EQ(complex_signal_move[5], 0);
}

// Test the copy assignment operator
TEST(complex_signal_operator, copy) {
    Complex_Signal complex_signal("001110");
    Complex_Signal complex_signal_copy;
    complex_signal_copy = complex_signal;
    EXPECT_EQ(complex_signal_copy[0], 0);
    EXPECT_EQ(complex_signal_copy[1], 0);
    EXPECT_EQ(complex_signal_copy[2], 1);
    EXPECT_EQ(complex_signal_copy[3], 1);
    EXPECT_EQ(complex_signal_copy[4], 1);
    EXPECT_EQ(complex_signal_copy[5], 0);
}

// Test the copy assignment operator
TEST(complex_signal_operator, copy_yourself) {
    Complex_Signal complex_signal("001110");
    complex_signal = complex_signal;
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 0);
}

// Test the move assignment operator
TEST(complex_signal_operator, move) {
    Complex_Signal complex_signal("001110");
    Complex_Signal complex_signal_move;
    complex_signal_move = std::move(complex_signal);
    EXPECT_EQ(complex_signal_move[0], 0);
    EXPECT_EQ(complex_signal_move[1], 0);
    EXPECT_EQ(complex_signal_move[2], 1);
    EXPECT_EQ(complex_signal_move[3], 1);
    EXPECT_EQ(complex_signal_move[4], 1);
    EXPECT_EQ(complex_signal_move[5], 0);
}

// Test the inversion
TEST(complex_signal_inversion, inversion) {
    Complex_Signal complex_signal("001110");
    complex_signal.inverstion();
    EXPECT_EQ(complex_signal[0], 1);
    EXPECT_EQ(complex_signal[1], 1);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 1);
}

// Test the inversion operator
TEST(complex_signal_operator, inversion) {
    Complex_Signal complex_signal("001110");
    ~complex_signal;
    EXPECT_EQ(complex_signal[0], 1);
    EXPECT_EQ(complex_signal[1], 1);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 1);
}

// Test the addition operator
TEST(complex_signal_operator, addition_valid) {
    Complex_Signal complex_signal("001");
    Complex_Signal complex_signal2("010");
    complex_signal += complex_signal2;
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 0);
}

// Test the addition operator yourself
TEST(complex_signal_operator, addition_yourself) {
    Complex_Signal complex_signal("001");
    complex_signal += complex_signal;
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 1);
}

// Test the addition operator sequentially
TEST(complex_signal_operator, addition_sequentially) {
    Complex_Signal complex_signal("001");
    complex_signal += complex_signal += complex_signal;
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 1);
    EXPECT_EQ(complex_signal[6], 0);
    EXPECT_EQ(complex_signal[7], 0);
    EXPECT_EQ(complex_signal[8], 1);
}

// Test the insertion with split
TEST(complex_signal_insert, insert_split_2) {
    Complex_Signal complex_signal("00111");
    Complex_Signal complex_signal2("010");
    complex_signal.insert(complex_signal2, 3);
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 0);
    EXPECT_EQ(complex_signal[6], 1);
    EXPECT_EQ(complex_signal[7], 1);
}

// Test the insertion with insert yourself
TEST(complex_signal_insert, insert_yourself) {
    Complex_Signal complex_signal("001");
    complex_signal.insert(complex_signal, 1);
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 1);
}

// Test the insertion with split
TEST(complex_signal_insert, insert_split) {
    Complex_Signal complex_signal("001");
    Complex_Signal complex_signal2("010");
    complex_signal.insert(complex_signal2, 1);
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 1);
}

// Test the insertion with insert before
TEST(complex_signal_insert, insert_before) {
    Complex_Signal complex_signal("001");
    Complex_Signal complex_signal2("010");
    complex_signal.insert(complex_signal2, 2);
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 1);
}

// Test the insertion with insert begining
TEST(complex_signal_insert, insert_begining) {
    Complex_Signal complex_signal("001");
    Complex_Signal complex_signal2("010");
    complex_signal.insert(complex_signal2, 0);
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 1);
    EXPECT_EQ(complex_signal[2], 0);
    EXPECT_EQ(complex_signal[3], 0);
    EXPECT_EQ(complex_signal[4], 0);
    EXPECT_EQ(complex_signal[5], 1);
}

// Test the insertion with invalid large
TEST(complex_signal_insert, insert_invalid_large) {
    Complex_Signal complex_signal("001");
    Complex_Signal complex_signal2("010");
    EXPECT_THROW(complex_signal.insert(complex_signal2, 10), std::out_of_range);
}

// Test the insertion with invalid zero
TEST(complex_signal_insert, insert_invalid_negative) {
    Complex_Signal complex_signal("001");
    Complex_Signal complex_signal2("010");
    EXPECT_THROW(complex_signal.insert(complex_signal2, -1), std::out_of_range);
}

//Test the multiply operator
TEST(complex_signal_operator, multiply_valid) {
    Complex_Signal complex_signal("001");
    Complex_Signal res = complex_signal * 2;
    EXPECT_EQ(res[0], 0);
    EXPECT_EQ(res[1], 0);
    EXPECT_EQ(res[2], 0);
    EXPECT_EQ(res[3], 0);
    EXPECT_EQ(res[4], 1);
    EXPECT_EQ(res[5], 1);
}

//Test the multiply operator with zero
TEST(complex_signal_operator, multiply_zero) {
    Complex_Signal complex_signal("001");
    Complex_Signal res = complex_signal * 0;
    EXPECT_THROW(res[0], std::out_of_range);
}

//Test the multiply operator with negative
TEST(complex_signal_operator, multiply_negative) {
    Complex_Signal complex_signal("001");
    EXPECT_THROW(complex_signal * -1, std::invalid_argument);
}

//Test format print
TEST(complex_signal_print, valid) {
    Complex_Signal complex_signal("001");
    std::wostringstream out;
    complex_signal.format_print(out);
    EXPECT_EQ(out.str(), std::wstring(L"__/‾"));
}

//Test format print
TEST(complex_signal_print, valid_2) {
    Complex_Signal complex_signal("0010");
    std::wostringstream out;
    complex_signal.format_print(out);
    EXPECT_EQ(out.str(), std::wstring(L"__/‾\\_"));
}

//Test format print
TEST(complex_signal_print, valid_3) {
    Complex_Signal complex_signal(0, 0);
    std::wostringstream out;
    complex_signal.format_print(out);
    EXPECT_EQ(out.str(), std::wstring(L""));
}

// Test operator <<
TEST(complex_signal_operator, output) {
    Complex_Signal complex_signal("0010");
    std::wostringstream out;
    out << complex_signal;
    EXPECT_EQ(out.str(), std::wstring(L"__/‾\\_"));
}

// Test operator >>
TEST(complex_signal_operator, input) {
    Complex_Signal complex_signal;
    std::istringstream in("001110");
    in >> complex_signal;
    EXPECT_EQ(complex_signal[0], 0);
    EXPECT_EQ(complex_signal[1], 0);
    EXPECT_EQ(complex_signal[2], 1);
    EXPECT_EQ(complex_signal[3], 1);
    EXPECT_EQ(complex_signal[4], 1);
    EXPECT_EQ(complex_signal[5], 0);
}