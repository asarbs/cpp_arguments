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
    argpars.addArgument({"--test_a", "-a", "help str0", val});
    argpars.addArgument({"--test_b", "-b", "help str1", val});
    argpars.addArgument({"--test_c", "-c", "help str2", val});
    argpars.addArgument({"--test_d", "-d", "help str2", val});
    argpars.addArgument({"--test_e", "-e", "help str2", val});
    argpars.parse(argc, argv);

    logger::logger << logger::info << "-a = " << argpars.getArgument<uint32_t>("-a").has_value() << "," << *argpars.getArgument<uint32_t>("-a") << logger::endl;
    logger::logger << logger::info << "-b = " << argpars.getArgument<uint32_t>("-b").has_value() << "," << *argpars.getArgument<uint32_t>("-b") << logger::endl;
    logger::logger << logger::info << "-c = " << argpars.getArgument<std::string>("-c").has_value() << "," << *argpars.getArgument<std::string>("-c") << logger::endl;
    logger::logger << logger::info << "-d = " << argpars.getArgument<uint32_t>("-d").has_value() << "," << *argpars.getArgument<std::string>("-d") << logger::endl;
    logger::logger << logger::info << "-e = " << argpars.getArgument<uint32_t>("-e").has_value() << "," << *argpars.getArgument<std::string>("-e") << logger::endl;

    uint32_t b_val = argpars.getArgument<uint32_t>("-b").value();
    uint32_t a_val = argpars.getArgument<uint32_t>("-a").value();

    logger::logger << logger::info << "b_val = " << b_val << logger::endl;
    logger::logger << logger::info << "a[" << a_val << "] * b[" << b_val << "] = " << (a_val * b_val) << logger::endl;
    logger::logger << logger::warning << "a[" << a_val << "] * b[" << b_val << "] = " << (a_val * b_val) << logger::endl;
    logger::logger << logger::error << "a[" << a_val << "] * b[" << b_val << "] = " << (a_val * b_val) << logger::endl;
    logger::logger << logger::critical << "a[" << a_val << "] * b[" << b_val << "] = " << (a_val * b_val) << logger::endl;

    return 0;
}
