#include <gtest/gtest.h>
#include "../src/utilities/exceptions.hpp"

TEST(ExceptionsTest, InvalidPositionException) {
    try {
        throw InvalidPositionException();
    } catch (const GameLogicException& e) {
        EXPECT_STREQ(e.what(), "Invalid summon position - too far from summoner");
    }
}

TEST(ExceptionsTest, NotEnoughEnergyException) {
    try {
        throw NotEnoughEnergyException(5, 10);
    } catch (const NotEnoughResourceException& e) {
        EXPECT_STREQ(e.what(), "Not enough energy: have 5, need 10");
    }
}

TEST(ExceptionsTest, SchoolNotFoundException) {
    try {
        throw SchoolNotFoundException(123);
    } catch (const GameLogicException& e) {
        EXPECT_STREQ(e.what(), "School not found: ID 123");
    }
}

TEST(ExceptionsTest, OutOfBoundsException) {
    try {
        throw OutOfBoundsException();
    } catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "Position is out of bounds");
    }
}

TEST(ExceptionsTest, ExceptionHierarchy) {
    try {
        throw NotEnoughEnergyException(5, 10);
    } catch (const GameException& e) {
        // Should catch as GameException
        SUCCEED();
        return;
    }
    FAIL() << "Exception was not caught as GameException";
}
