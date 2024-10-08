#include "arguments.h"

#include "logger.h"

std::ostream& operator<<(std::ostream& o, const VersionInfo& v) {
    o << v.major << "." << v.minor << "." << v.patch;
    if (v.build) {
        o << " (" << *v.build << ")";
    }

    return o;
}

std::ostream& operator<<(std::ostream& o, const Argument::Type& t) {
    switch (t) {
        case Argument::Type::uint8:
            return o << "uint8";
        case Argument::Type::uint16:
            return o << "uint16";
        case Argument::Type::uint32:
            return o << "uint32";
        case Argument::Type::uint64:
            return o << "uint64";
        case Argument::Type::int8:
            return o << "int8";
        case Argument::Type::int16:
            return o << "int16";
        case Argument::Type::int32:
            return o << "int32";
        case Argument::Type::int64:
            return o << "int64";
        case Argument::Type::string:
            return o << "string";
        default:
            return o << "Unknown";
    }
}

logger::Logger& operator<<(logger::Logger& logger, const Argument::Type& t) {
    switch (t) {
        case Argument::Type::uint8:
            return logger << "uint8";
        case Argument::Type::uint16:
            return logger << "uint16";
        case Argument::Type::uint32:
            return logger << "uint32";
        case Argument::Type::uint64:
            return logger << "uint64";
        case Argument::Type::int8:
            return logger << "int8";
        case Argument::Type::int16:
            return logger << "int16";
        case Argument::Type::int32:
            return logger << "int32";
        case Argument::Type::int64:
            return logger << "int64";
        case Argument::Type::string:
            return logger << "string";
        default:
            return logger << "Unknown";
    }
}

Argument::ArgumentValue::ArgumentValue(Type type, char* value) : __type(type), __value_str(value){};

Argument::ArgumentValue::ArgumentValue(const Argument::ArgumentValue& other) : __type(other.__type), __value_str(nullptr) {
    if (other.__value_str) {
        __value_str = new char[std::strlen(other.__value_str) + 1];
        std::strcpy(__value_str, other.__value_str);
    }
};

Argument::ArgumentValue::ArgumentValue(Argument::ArgumentValue&& other) noexcept : __type(other.__type), __value_str(other.__value_str) {
    other.__value_str = NULL;
};

Argument::ArgumentValue& Argument::ArgumentValue::operator=(const Argument::ArgumentValue& other) {
    if (this != &other) {
        delete __value_str;
        __type = other.__type;
        if (other.__value_str != NULL) {
            size_t val_str_size = std::strlen(other.__value_str) + 1;
            __value_str         = new char[val_str_size];
            std::strcpy(__value_str, other.__value_str);
        } else {
            __value_str = NULL;
        }
    }
    return *this;
};

Argument::ArgumentValue& Argument::ArgumentValue::operator=(Argument::ArgumentValue&& other) noexcept {
    if (this != &other) {
        delete __value_str;
        __type            = other.__type;
        __value_str       = other.__value_str;
        other.__value_str = NULL;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& o, const Argument::ArgumentValue& v) {
    o << "[" << v.__type << ":" << v.__value_str << "]";
    return o;
}

logger::Logger& operator<<(logger::Logger& logger, const Argument::ArgumentValue& v) {
    logger << "[" << v.__type << ":" << v.__value_str << "]";
    return logger;
}

void Argument::ArgumentValue::setValue(char* value_str) {
    __value_str = value_str;
}

void Argument::setValue(char* value_str) {
    __value.setValue(value_str);
}

Argument::Argument() : __name(""), __flag(""), __help(""), __value(Argument::Type::NONE, NULL) {
}

Argument::Argument(std::string name, std::string flag, std::string help, Type type, char* value)
    : __name(name), __flag(flag), __help(help), __value(type, value) {
}

Argument::Argument(const Argument& other) : __name(other.__name), __flag(other.__flag), __help(other.__help), __value(other.__value){};

Argument::Argument(Argument&& other) : __name(other.__name), __flag(other.__flag), __help(other.__help), __value(other.__value){};

bool Argument::operator==(const char* other) const {
    return __name == other || __flag == other;
}

Argument& Argument::operator=(const Argument& other) noexcept {
    __name  = other.__name;
    __flag  = other.__flag;
    __help  = other.__help;
    __value = other.__value;
    return *this;
};

Argument& Argument::operator=(Argument&& other) noexcept {
    __name  = other.__name;
    __flag  = other.__flag;
    __help  = other.__help;
    __value = other.__value;
    return *this;
};

char* Argument::ArgumentValue::getValue() const {
    return __value_str;
}

std::string Argument::getName() const {
    return __name;
}

std::string Argument::getFlag() const {
    return __flag;
}

std::string Argument::getValue() const {
    if (__value.getValue() == NULL) {
        return std::string("NULL");
    }
    return std::string(__value.getValue());
}

ArgumentParser::ArgumentParser(const std::string& prog_name, const VersionInfo& version) : __prog_name(prog_name), __version(version) {
}

ArgumentParser& ArgumentParser::getInstance(const std::string& prog_name, const VersionInfo& ver) {
    static ArgumentParser instance(prog_name, ver);
    return instance;
}

void ArgumentParser::parse(const int argc, char* argv[]) {
    std::vector<std::pair<char*, char*>> mainArgs;
    const char                           constant = '-';

    for (uint32_t argIndex = 1; argIndex < argc; argIndex++) {
        if (argv[argIndex][0] == constant) {
            mainArgs.push_back({argv[argIndex], NULL});

        } else {
            mainArgs.back().second = argv[argIndex];
        }
    }

    for (const auto& a : mainArgs) {
        for (auto& arg : __arguments) {
            if (arg == a.first) {
                arg.setValue(a.second);
                logger::logger << logger::debug << "update argument value:" <<            //
                    logger::setw(5) << a.first << "=" <<                                  //
                    logger::setw(15) << (a.second == NULL ? "NULL" : a.second) <<         //
                    " => " <<                                                             //
                    logger::setw(15) << arg.getName() << "[" << arg.getFlag() << "]=" <<  //
                    logger::setw(15) << arg.getValue() << logger::endl;
            }
        }
    }
}

void ArgumentParser::addArgument(Argument arg) {
    logger::logger << logger::debug << "Add argument \"" << arg.getName() << "[" << arg.getFlag() << "] -> " << arg.getValue()
                   << "\" to Argument Parser." << logger::endl;
    __arguments.push_back(std::move(arg));
}
