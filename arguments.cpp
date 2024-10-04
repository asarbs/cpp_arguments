#include "arguments.h"

#include "logger.h"

std::ostream& operator<<(std::ostream& o, const VersionInfo& v) {
    o << v.major << "." << v.minor << "." << v.patch;
    if (v.build) {
        o << " (" << *v.build << ")";
    }

    return o;
}

template <class T>
Argument<T>::Argument() {
}


ArgumentParser::ArgumentParser(const std::string& prog_name, const VersionInfo& version) : __prog_name(prog_name), __version(version) {
}

ArgumentParser& ArgumentParser::getInstance(int argc, char* argv[], const std::string& prog_name, const VersionInfo& ver) {
    for (uint32_t x = 1; x < argc; x++) {
        logger::logger << logger::debug << argv[x] << logger::endl;
    }

    static ArgumentParser instance(prog_name, ver);
    return instance;
}

void ArgumentParser::addArgument(const Argument& arg) {
    logger::logger << logger::debug << arg.getParamValue() << logger::endl;
}
