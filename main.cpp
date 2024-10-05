#include <iostream>
#include <bitset>
#include <memory>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <iomanip>
#include <mutex>
#include <typeinfo>

#include "logger.h"
#include "arguments.h"

int main(int argc, char* argv[]) {
    logger::logger.setLogLevel(logger::debug);

    ArgumentParser& argpars = ArgumentParser::getInstance(argc, argv, "test app", {12, 13, 4, "a0e67de04e79"});
    char*           val     = (char*)"-1";
    argpars.addArgument({"--test_a", "-a", "help str0", Argument::Type::uint8, val});
    argpars.addArgument({"--test_b", "-b", "help str1", Argument::Type::uint8, val});
    argpars.addArgument({"--test_c", "-c", "help str2", Argument::Type::uint8, val});
    argpars.addArgument({"--test_d", "-d", "help str2", Argument::Type::uint8, val});
    argpars.addArgument({"--test_e", "-e", "help str2", Argument::Type::uint8, val});

    (void)(argpars);

    return 0;
}
