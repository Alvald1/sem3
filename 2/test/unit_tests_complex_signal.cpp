#include <limits>

#include <gtest/gtest.h>
#include "../complex_signal/complex_signal.hpp"

TEST(complex_signal_constructor, level_duration) { Complex_Signal complex_signal(1, 10); }