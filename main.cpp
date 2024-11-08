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

    Argument::ArgumentParser& argpars = Argument::ArgumentParser::getInstance("test app", {12, 13, 4, "a0e67de04e79"});
    char* val = (char*)"-1";
    argpars.addArgument("--test_a", Argument::Action::Store, "-a", "help str0", val);
    argpars.addArgument("--test_b", Argument::Action::Store, "-b", "help str1", val);
    argpars.addArgument("--test_c", Argument::Action::Store, "-c", "help str3", val);
    argpars.addArgument("--test_d", Argument::Action::Store, "-d", "help str4", val);
    argpars.addArgument("--test_e", Argument::Action::StoreBool, "-e", "help str5", val);
    argpars.addArgument("--test_f", Argument::Action::Store, "-f", "help str5", val);
    argpars.parse(argc, argv);

    std::optional<uint32_t> arg_a = argpars.getArgument<uint32_t>("-a");
    logger::logger << logger::info << "-a = " << arg_a.has_value() << "," << *arg_a << logger::endl;

    std::optional<uint32_t> arg_b = argpars.getArgument<uint32_t>("-b");
    logger::logger << logger::info << "-b = " << arg_b.has_value() << "," << *arg_b << logger::endl;

    std::optional<std::string> arg_c = argpars.getArgument<std::string>("-c");
    logger::logger << logger::info << "-c = " << arg_c.has_value() << "," << *arg_c << logger::endl;

    std::optional<uint32_t> arg_d = argpars.getArgument<uint32_t>("-d");
    logger::logger << logger::info << "-d = " << arg_d.has_value() << "," << *arg_d << logger::endl;

    std::optional<bool> arg_e = argpars.getArgument<bool>("-e");
    logger::logger << logger::info << "-e = " << arg_e.has_value() << "," << *arg_e << logger::endl;

    std::optional<int32_t> arg_f = argpars.getArgument<int32_t>("-f");
    logger::logger << logger::info << "-f = " << arg_f.has_value() << "," << *arg_f << logger::endl;

    uint32_t b_val = arg_b.value();
    uint32_t a_val = arg_a.value();

    logger::logger << logger::info << "b_val = " << b_val << logger::endl;
    logger::logger << logger::info << "a[" << a_val << "] * b[" << b_val << "] = " << (a_val * b_val) << logger::endl;
    logger::logger << logger::warning << "a[" << a_val << "] * b[" << b_val << "] = " << (a_val * b_val) << logger::endl;
    logger::logger << logger::error << "a[" << a_val << "] * b[" << b_val << "] = " << (a_val * b_val) << logger::endl;
    logger::logger << logger::critical << "a[" << a_val << "] * b[" << b_val << "] = " << (a_val * b_val) << logger::endl;

    return 0;
}
