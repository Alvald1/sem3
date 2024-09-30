#include <gtest/gtest.h>
#include "../signal.hpp"

// Test the constructor and getters
TEST(SignalTest, ConstructorAndGetters) {
    Signal signal(1, 10);
    EXPECT_EQ(signal.get_level(), 1);
    EXPECT_EQ(signal.get_duration(), 10);
}

// Test setting valid duration
TEST(SignalTest, SetValidDuration) {
    Signal signal(1, 10);
    signal.set_duration(20);
    EXPECT_EQ(signal.get_duration(), 20);
}

// Test setting invalid duration
TEST(SignalTest, SetInvalidDuration) {
    Signal signal(1, 10);
    EXPECT_THROW(signal.set_duration(-5), std::invalid_argument);
}

// Test setting valid level
TEST(SignalTest, SetValidLevel) {
    Signal signal(1, 10);
    signal.set_level(0);
    EXPECT_EQ(signal.get_level(), 0);
}

// Test setting invalid level
TEST(SignalTest, SetInvalidLevel) {
    Signal signal(1, 10);
    EXPECT_THROW(signal.set_level(2), std::invalid_argument);
}

// Initializes Signal object with valid binary string "0" or "1"
TEST(SignalTest, shouldInitializeSignalObjectWhenGivenValidBinaryString) {
    std::string valid_binary_string = "000111";
    Signal signal(valid_binary_string);
    EXPECT_EQ(signal.get_duration(), valid_binary_string.length());
    EXPECT_EQ(signal.get_level(), valid_binary_string[0] - '0');
}

// Handles empty string input
TEST(SignalTest, shouldThrowInvalidArgumentWhenGivenEmptyString) {
    std::string empty_string = "";
    EXPECT_THROW({ Signal signal(empty_string); }, std::invalid_argument);
}

// Inverting the signal level from 0 to 1
TEST(Inversion, should_set_level_to_1_when_initial_level_is_0) {
    Signal signal;
    signal.inversion();
    EXPECT_EQ(signal.get_level(), 1);
}