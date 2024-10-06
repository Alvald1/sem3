#include <limits>

#include <gtest/gtest.h>
#include "../allocator/allocator.hpp"

// Test the constructor with valid value
TEST(constractor, valid_value) {
    Allocator allocator(10);
    EXPECT_EQ(allocator.size_, 0);
    EXPECT_EQ(allocator.capacity_, 10);
}

TEST(constractor, default) {
    Allocator allocator;
    EXPECT_EQ(allocator.size_, 0);
    EXPECT_EQ(allocator.capacity_, 0);
    EXPECT_EQ(allocator.buffer, nullptr);
}

// Test the constructor with invalid value zero
TEST(constractor, invalid_value_zero) { EXPECT_THROW(Allocator allocator(0), std::invalid_argument); }

// Test the constructor with invalid value negative
TEST(constractor, invalid_value_negative) { EXPECT_THROW(Allocator allocator(-5), std::invalid_argument); }

// Test the constructor bad_alloc
TEST(constructor, bad_alloc) { EXPECT_THROW(Allocator allocator(std::numeric_limits<int>::max()), std::bad_alloc); }

// Test the resize function with valid value no expand 1
TEST(resize, valid_value_no_expand_1) {
    Allocator allocator(10);
    allocator.resize(5);
    EXPECT_EQ(allocator.capacity_, 10);
}

// Test the resize function with valid value no expand 2
TEST(resize, valid_value_no_expand_2) {
    Allocator allocator(10);
    allocator.resize(0);
    EXPECT_EQ(allocator.capacity_, 10);
}

// Test the resize function with valid value no expand 3
TEST(resize, valid_value_no_expand_3) {
    Allocator allocator(10);
    allocator.size_ = 1;
    allocator.resize(0);
    EXPECT_EQ(allocator.capacity_, 10);
}

TEST(resize, default_constuctor) {
    Allocator allocator;
    allocator.resize(10);
    EXPECT_EQ(allocator.capacity_, 10);
}

// Test the resize function with valid value expand
TEST(resize, valid_value_expand_1) {
    Allocator allocator(10);
    allocator.resize(15);
    EXPECT_EQ(allocator.capacity_, 20);
}

// Test the resize function with valid value expand 2
TEST(resize, valid_value_expand_2) {
    Allocator allocator(10);
    allocator.size_ = 6;
    allocator.resize(5);
    EXPECT_EQ(allocator.capacity_, 20);
}

// Test the resize function with invalid value negative
TEST(resize, invalid_value_negative) {
    Allocator allocator(10);
    EXPECT_THROW(allocator.resize(-5), std::invalid_argument);
}

TEST(resize, overflow) {
    Allocator allocator(10);
    EXPECT_THROW(allocator.resize(std::numeric_limits<int>::max()), std::overflow_error);
}