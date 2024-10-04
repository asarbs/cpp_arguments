#include "gtest/gtest.h"

#include <stdexcept>
#include <exception>

class LoggerMain : public testing::Test {};

TEST_F(LoggerMain, simple_text_debug) {
    EXPECT_EQ(true, false);
}
