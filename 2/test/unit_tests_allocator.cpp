#include <limits>

#include <gtest/gtest.h>
#include "../allocator/allocator.hpp"

// Test the constructor with valid value
TEST(allocator_constructor, valid_value) {
    Allocator allocator(10);
    EXPECT_EQ(allocator.size_, 1);
    EXPECT_EQ(allocator.capacity_, 11);
}

TEST(allocator_constructor, default) {
    Allocator allocator;
    EXPECT_EQ(allocator.size_, 1);
    EXPECT_EQ(allocator.capacity_, 1);
}

// Test the constructor with invalid value zero
TEST(allocator_constructor, invalid_value_zero) { EXPECT_THROW(Allocator allocator(0), std::invalid_argument); }

// Test the constructor with invalid value negative
TEST(allocator_constructor, invalid_value_negative) { EXPECT_THROW(Allocator allocator(-5), std::invalid_argument); }

// Test the constructor bad_alloc
TEST(allocator_constructor, bad_alloc) {
    EXPECT_THROW(Allocator allocator(std::numeric_limits<int>::max()), std::bad_alloc);
}

// Test the resize function with valid value no expand 1
TEST(allocator_resize, valid_value_no_expand_1) {
    Allocator allocator(10);
    allocator.resize(5);
    EXPECT_EQ(allocator.capacity_, 11);
}

// Test the resize function with valid value no expand 2
TEST(allocator_resize, valid_value_no_expand_2) {
    Allocator allocator(10);
    allocator.resize(0);
    EXPECT_EQ(allocator.capacity_, 11);
}

TEST(allocator_resize, default_constuctor) {
    Allocator allocator;
    allocator.resize(10);
    EXPECT_EQ(allocator.capacity_, 11);
}

// Test the resize function with valid value expand
TEST(allocator_resize, valid_value_expand_1) {
    Allocator allocator(10);
    allocator.resize(15);
    EXPECT_EQ(allocator.capacity_, 22);
}

// Test the resize function with valid value expand 2
TEST(allocator_resize, valid_value_expand_2) {
    Allocator allocator(10);
    allocator.size_ = 6;
    allocator.resize(6);
    EXPECT_EQ(allocator.capacity_, 22);
}

// Test the resize function with invalid value negative
TEST(allocator_resize, invalid_value_negative) {
    Allocator allocator(10);
    EXPECT_THROW(allocator.resize(-5), std::invalid_argument);
}

// Test the resize function with invalid value overflow
TEST(allocator_resize, overflow) {
    Allocator allocator(10);
    EXPECT_THROW(allocator.resize(std::numeric_limits<int>::max()), std::overflow_error);
}

// Test the copy constructor
TEST(allocator_constructor, copy_constructor) {
    Allocator allocator(10);
    Allocator allocator2(allocator);
    EXPECT_EQ(allocator2.size_, 1);
    EXPECT_EQ(allocator2.capacity_, 11);
}

// Test the move constructor
TEST(allocator_constructor, move_constructor) {
    Allocator allocator(10);
    Allocator allocator2(std::move(allocator));
    EXPECT_EQ(allocator2.size_, 1);
    EXPECT_EQ(allocator2.capacity_, 11);
}

// Test the copy assignment operator
TEST(allocator_operator, copy) {
    Allocator allocator(10);
    Allocator allocator2;
    allocator2 = allocator;
    EXPECT_EQ(allocator2.size_, 1);
    EXPECT_EQ(allocator2.capacity_, 11);
}

// Test the copy assignment operator yourself
TEST(allocator_operator, copy_yourself) {
    Allocator allocator(10);
    allocator = allocator;
    EXPECT_EQ(allocator.size_, 1);
    EXPECT_EQ(allocator.capacity_, 11);
}

// Test the move assignment operator
TEST(allocator_operator, move) {
    Allocator allocator(10);
    Allocator allocator2;
    allocator2 = std::move(allocator);
    EXPECT_EQ(allocator2.size_, 1);
    EXPECT_EQ(allocator2.capacity_, 11);
}