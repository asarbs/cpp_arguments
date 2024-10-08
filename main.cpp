#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <bitset>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <typeinfo>

#include "arguments.h"
#include "logger.h"

int main(int argc, char* argv[]) {
    logger::logger.setLogLevel(logger::info);

    ArgumentParser& argpars = ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});
    char*           val     = (char*)"-1";
    argpars.addArgument({"--test_a", "-a", "help str0", Argument::Type::uint8, val});
    argpars.addArgument({"--test_b", "-b", "help str1", Argument::Type::uint8, val});
    argpars.addArgument({"--test_c", "-c", "help str2", Argument::Type::uint8, val});
    argpars.addArgument({"--test_d", "-d", "help str2", Argument::Type::uint8, val});
    argpars.addArgument({"--test_e", "-e", "help str2", Argument::Type::uint8, val});
    argpars.parse(argc, argv);

    logger::logger << logger::info << "-a = " << argpars.getArgumentUint32("-a").has_value() << "," << *argpars.getArgumentUint32("-a")
                   << logger::endl;
    logger::logger << logger::info << "-b = " << argpars.getArgumentUint32("-b").has_value() << "," << *argpars.getArgumentUint32("-b")
                   << logger::endl;
    logger::logger << logger::info << "-c = " << argpars.getArgumentStr("-c").has_value() << "," << *argpars.getArgumentStr("-c") << logger::endl;
    logger::logger << logger::info << "-d = " << argpars.getArgumentUint32("-d").has_value() << "," << *argpars.getArgumentStr("-d") << logger::endl;
    logger::logger << logger::info << "-e = " << argpars.getArgumentUint32("-e").has_value() << "," << *argpars.getArgumentStr("-e") << logger::endl;

    return 0;
}
