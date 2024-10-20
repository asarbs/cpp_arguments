#include <exception>
#include <stdexcept>

#include "arguments.h"
#include "gtest/gtest.h"

class LoggerMain : public testing::Test {};

TEST_F(LoggerMain, StoreParameter) {
    Argument::ArgumentParser& argpars = Argument::ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});

    char app_name[] = "test_app";
    char arg_1[] = "-a";
    char par_1[] = "42";
    int argc = 3;
    char* argv[] = {app_name, arg_1, par_1};
    char* val = (char*)"-1";

    argpars.addArgument({"--test_a", Argument::Argument::Action::Store, "-a", "help str0", val});
    EXPECT_EQ(argpars.getArgument<uint32_t>("-a"), -1);
    argpars.parse(argc, argv);
    EXPECT_EQ(argpars.getArgument<uint32_t>("-a"), 42);
}
