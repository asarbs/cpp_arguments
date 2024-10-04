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
    argpars.addArgument({});

    (void)(argpars);

    return 0;
}
