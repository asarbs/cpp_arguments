#include <exception>
#include <stdexcept>

#include "arguments.h"
#include "gtest/gtest.h"

class ArgumentsTest : public ::testing::Test {
   protected:
    // Code that will be executed once before all the tests
    static void SetUpTestSuite() {}

    // Code that will be executed once after all the tests
    static void TearDownTestSuite() {}

    // Code that will be executed before each test
    void SetUp() override { logger::logger.setLogLevel(logger::warning); }

    // Code that will be executed after each test
    void TearDown() override {}
};

TEST_F(ArgumentsTest, StoreParameter) {
    Argument::ArgumentParser& argpars = Argument::ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});

    char app_name[] = "test_app";
    char arg_1[] = "-a";
    char par_1[] = "42";
    int argc = 3;
    char* argv[] = {app_name, arg_1, par_1};
    char* val = (char*)"-1";

    argpars.addArgument("--test_a", Argument::Action::Store, "-a", "help str0", val);
    EXPECT_EQ(argpars.getArgument<uint32_t>("-a"), -1);
    argpars.parse(argc, argv);
    EXPECT_EQ(argpars.getArgument<uint32_t>("-a"), 42);
    argpars.reset();
}

TEST_F(ArgumentsTest, PrintVersion) {
    testing::internal::CaptureStdout();
    Argument::ArgumentParser& argpars = Argument::ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});

    char* val = (char*)"-1";
    argpars.addArgument("-version", Argument::Action::Version, "-v", "help str0", val);
    char app_name[] = "test_app";
    char arg_1[] = "-v";
    int argc = 2;
    char* argv[] = {app_name, arg_1};

    EXPECT_EXIT(argpars.parse(argc, argv), ::testing::ExitedWithCode(0), "");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "test app 12.13.4:a0e67de04e79\n");
    argpars.reset();
}

TEST_F(ArgumentsTest, PrintHelp) {
    testing::internal::CaptureStdout();
    Argument::ArgumentParser& argpars = Argument::ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});

    char* val = (char*)"-1";
    argpars.addArgument("--test_art", Argument::Action::Help, "-ta", "test str0", val);
    char app_name[] = "test_app";
    char arg_1[] = "-h";
    int argc = 2;
    char* argv[] = {app_name, arg_1};

    EXPECT_EXIT(argpars.parse(argc, argv), ::testing::ExitedWithCode(0), "");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output,
              "usage: test app [-ta] [-v] [-h]\noptions:\n  -ta, --test_art     test str0\n   -v, --version      show program's version number and exit\n   -h, --help         "
              "show this help message and exit\n");
    argpars.reset();
}

TEST_F(ArgumentsTest, getMinusValue) {
    Argument::ArgumentParser& argpars = Argument::ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});

    char app_name[] = "test_app";
    char arg_1[] = "-a";
    char par_1[] = "-42";
    int argc = 3;
    char* argv[] = {app_name, arg_1, par_1};
    char* val = (char*)"-1";

    argpars.addArgument("--test_a", Argument::Action::Store, "-a", "help str0", val);
    EXPECT_EQ(argpars.getArgument<uint32_t>("-a"), -1);
    argpars.parse(argc, argv);
    EXPECT_EQ(argpars.getArgument<uint32_t>("-a"), -42);
    argpars.reset();
}

TEST_F(ArgumentsTest, getBoolValuePresent) {
    Argument::ArgumentParser& argpars = Argument::ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});

    char app_name[] = "test_app";
    char arg_1[] = "-a";
    int argc = 2;
    char* argv[] = {app_name, arg_1};

    char* val = (char*)"-1";

    argpars.addArgument("--test_a", Argument::Action::StoreBool, "-a", "help str0", val);
    argpars.parse(argc, argv);
    EXPECT_EQ(argpars.getArgument<bool>("-a"), true);
    argpars.reset();
}

TEST_F(ArgumentsTest, getBoolValueAbsent) {
    Argument::ArgumentParser& argpars = Argument::ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});

    char app_name[] = "test_app";
    char arg_1[] = "-b";
    int argc = 2;
    char* argv[] = {app_name, arg_1};

    char* val = (char*)"-1";

    argpars.addArgument("--test_a", Argument::Action::StoreBool, "-a", "help str0", val);
    argpars.addArgument("--test_a", Argument::Action::Store, "-b", "help str0", val);
    argpars.parse(argc, argv);
    EXPECT_EQ(argpars.getArgument<bool>("-a"), false);
    argpars.reset();
}