#include "gtest/gtest.h"

#include <stdexcept>
#include <exception>

#include "arguments.h"

class LoggerMain : public testing::Test {};

TEST_F(LoggerMain, one_parameter_with_one_value) {
    ArgumentParser& argpars = ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});

    char  app_name[] = "test_app";
    char  arg_1[]    = "-a";
    char  par_1[]    = "42";
    int   argc       = 3;
    char* argv[]     = {app_name, arg_1, par_1};
    char* val        = (char*)"-1";

    argpars.addArgument({"--test_a", "-a", "help str0", Argument::Type::uint8, val});
    EXPECT_EQ(argpars.getArgumentUint32("-a"), -1);
    argpars.parse(argc, argv);
    EXPECT_EQ(argpars.getArgumentUint32("-a"), 42);
}
