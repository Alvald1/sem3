#include <limits>

#include <gtest/gtest.h>
#include "../signal.hpp"

// Test the constructor and getters
TEST(constructor, constructor_and_getters) {
    Signal signal(1, 10);
    EXPECT_EQ(signal.get_level(), 1);
    EXPECT_EQ(signal.get_duration(), 10);
}

// Test setting valid duration
TEST(set_get, set_valid_duration) {
    Signal signal(1, 10);
    signal.set_duration(20);
    EXPECT_EQ(signal.get_duration(), 20);
}

// Test setting invalid duration
TEST(set_get, set_invalid_duration) {
    Signal signal(1, 10);
    EXPECT_THROW(signal.set_duration(-5), std::invalid_argument);
}

// Test setting valid level
TEST(set_get, set_valid_level) {
    Signal signal(1, 10);
    signal.set_level(0);
    EXPECT_EQ(signal.get_level(), 0);
}

// Test setting invalid level
TEST(set_get, set_invalid_level) {
    Signal signal(1, 10);
    EXPECT_THROW(signal.set_level(2), std::invalid_argument);
}

// Initializes Signal object with valid binary string "0" or "1"
TEST(constructor, should_initialize_signal_object_when_given_valid_binary_string) {
    std::string valid_binary_string = "000111";
    Signal signal(valid_binary_string);
    EXPECT_EQ(signal.get_duration(), 3);
    EXPECT_EQ(signal.get_level(), 0);
}

// Initializes Signal object with valid binary string "0" or "1" or any
TEST(constructor, should_initialize_signal_object_when_given_valid_binary_string_2) {
    std::string valid_binary_string = "111aaa";
    Signal signal(valid_binary_string);
    EXPECT_EQ(signal.get_duration(), 3);
    EXPECT_EQ(signal.get_level(), 1);
}

// Initializes Signal object with invalid string
TEST(constructor, should_initialize_signal_object_when_given_invalid_string) {
    std::string invalid_binary_string = "qq111aaa";
    EXPECT_THROW({ Signal signal(invalid_binary_string); }, std::invalid_argument);
}

// Handles empty string input
TEST(constructor, should_throw_invalid_argument_when_given_empty_string) {
    std::string empty_string = "";
    EXPECT_THROW({ Signal signal(empty_string); }, std::invalid_argument);
}

// Inverting the signal level from 0 to 1
TEST(inversion, should_set_level_to_1_when_initial_level_is_0) {
    Signal signal;
    signal.inversion();
    EXPECT_EQ(signal.get_level(), 1);
}

// Operator ~ should correctly invert the signal
TEST(inversion, should_invert_the_signal_when_operator_is_used) {
    Signal signal(1, 1);
    ~signal;
    EXPECT_EQ(signal.get_level(), 0);
}

// Operator ~ should correctly double invert the signal
TEST(inversion, should_invert_the_signal_when_operator_is_used_double) {
    Signal signal(1, 1);
    ~~signal;
    EXPECT_EQ(signal.get_level(), 1);
}

// increase duration_ by a positive integer value
TEST(increase, should_increase_duration_when_value_is_positive) {
    Signal signal;
    int initial_duration = signal.get_duration();
    int increase_value = 5;
    signal.increase(increase_value);
    EXPECT_EQ(signal.get_duration(), initial_duration + increase_value);
}

// throw invalid_argument when value is negative
TEST(increase, should_throw_invalid_argument_when_value_is_negative) {
    Signal signal;
    int negative_value = -5;
    EXPECT_THROW(signal.increase(negative_value), std::invalid_argument);
}

// throw overflow_error when addition of value to duration_ exceeds max int limit
TEST(increase, increase_overflow) {
    Signal signal(0, std::numeric_limits<int>::max() - 5);
    EXPECT_THROW(signal.increase(10), std::overflow_error);
}

// Decrease duration_ by a positive integer less than duration_
TEST(decrease, should_decrease_duration_when_value_is_a_positive_integer_less_than_duration) {
    Signal signal(0, 10);
    signal.decrease(5);
    EXPECT_EQ(signal.get_duration(), 5);
}

// Decrease duration_ by a value greater than duration_
TEST(decrease, decrease_by_value_greater_than_duration) {
    Signal signal(0, 10);
    EXPECT_THROW(signal.decrease(15), std::underflow_error);
}

// Decrease duration_ by a negative integer
TEST(decrease, decrease_by_negative_integer) {
    Signal signal(0, 10);
    EXPECT_THROW(signal.decrease(-5), std::invalid_argument);
}

// Correctly formats and prints a string based on duration_ and level_ = 1
TEST(format_print, should_correctly_format_and_print_string_when_duration_and_level_are_set_1) {
    Signal signal("111");
    std::wostringstream out;
    signal.format_print(out);
    EXPECT_EQ(out.str(), std::wstring(L"‾‾‾\n"));
}

// Correctly formats and prints a string based on duration_ and level_ = 0
TEST(format_print, should_correctly_format_and_print_string_when_duration_and_level_are_set_0) {
    Signal signal("000");
    std::wostringstream out;
    signal.format_print(out);
    EXPECT_EQ(out.str(), std::wstring(L"___\n"));
}

// Handles duration_ set to zro
TEST(format_print, should_handle_zero_duration_correctly) {
    Signal signal(0, 0);
    std::wostringstream out;
    signal.format_print(out);
    EXPECT_EQ(out.str(), std::wstring(L"\n"));
}