#include <limits>

#include <gtest/gtest.h>
#include "../signal.hpp"

// Test the constructor and getters
TEST(Constructor, ConstructorAndGetters) {
    Signal signal(1, 10);
    EXPECT_EQ(signal.get_level(), 1);
    EXPECT_EQ(signal.get_duration(), 10);
}

// Test setting valid duration
TEST(Set_get, SetValidDuration) {
    Signal signal(1, 10);
    signal.set_duration(20);
    EXPECT_EQ(signal.get_duration(), 20);
}

// Test setting invalid duration
TEST(Set_get, SetInvalidDuration) {
    Signal signal(1, 10);
    EXPECT_THROW(signal.set_duration(-5), std::invalid_argument);
}

// Test setting valid level
TEST(Set_get, SetValidLevel) {
    Signal signal(1, 10);
    signal.set_level(0);
    EXPECT_EQ(signal.get_level(), 0);
}

// Test setting invalid level
TEST(Set_get, SetInvalidLevel) {
    Signal signal(1, 10);
    EXPECT_THROW(signal.set_level(2), std::invalid_argument);
}

// Initializes Signal object with valid binary string "0" or "1"
TEST(Constructor, shouldInitializeSignalObjectWhenGivenValidBinaryString) {
    std::string valid_binary_string = "000111";
    Signal signal(valid_binary_string);
    EXPECT_EQ(signal.get_duration(), valid_binary_string.length());
    EXPECT_EQ(signal.get_level(), valid_binary_string[0] - '0');
}

// Handles empty string input
TEST(Constructor, shouldThrowInvalidArgumentWhenGivenEmptyString) {
    std::string empty_string = "";
    EXPECT_THROW({ Signal signal(empty_string); }, std::invalid_argument);
}

// Inverting the signal level from 0 to 1
TEST(Inversion, should_set_level_to_1_when_initial_level_is_0) {
    Signal signal;
    signal.inversion();
    EXPECT_EQ(signal.get_level(), 1);
}

TEST(Inversion, should_set_level_to_0_when_initial_level_is_1) {
    Signal signal(1, 0);
    signal.inversion();
    EXPECT_EQ(signal.get_level(), 0);
}

// increase duration_ by a positive integer value
TEST(Increase, should_increase_duration_when_value_is_positive) {
    Signal signal;
    int initial_duration = signal.get_duration();
    int increase_value = 5;
    signal.increase(increase_value);
    EXPECT_EQ(signal.get_duration(), initial_duration + increase_value);
}

// throw invalid_argument when value is negative
TEST(Increase, should_throw_invalid_argument_when_value_is_negative) {
    Signal signal;
    int negative_value = -5;
    EXPECT_THROW(signal.increase(negative_value), std::invalid_argument);
}

// throw overflow_error when addition of value to duration_ exceeds max int limit
TEST(Increase, IncreaseOverflow) {
    Signal signal(0, std::numeric_limits<int>::max() - 5);
    EXPECT_THROW(signal.increase(10), std::overflow_error);
}

// Decrease duration_ by a positive integer less than duration_
TEST(Decrease, should_decrease_duration_when_value_is_a_positive_integer_less_than_duration_) {
    Signal signal(0, 10);
    signal.decrease(5);
    EXPECT_EQ(signal.get_duration(), 5);
}

// Decrease duration_ by a value greater than duration_
TEST(Decrease, DecreaseByValueGreaterThanDuration) {
    Signal signal(0, 10);
    EXPECT_THROW(signal.decrease(15), std::underflow_error);
}

// Decrease duration_ by a negative integer
TEST(Decrease, DecreaseByNegativeInteger) {
    Signal signal(0, 10);
    EXPECT_THROW(signal.decrease(-5), std::invalid_argument);
}
