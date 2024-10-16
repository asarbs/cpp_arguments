#include "arguments.h"

#include "logger.h"

std::ostream& operator<<(std::ostream& o, const VersionInfo& v) {
    o << v.major << "." << v.minor << "." << v.patch;
    if (v.build) {
        o << " (" << *v.build << ")";
    }

    return o;
}

Argument::ArgumentValue::ArgumentValue(char* value) {
    if (value == NULL) {
        __value_str = "";
    } else {
        __value_str = value;
    }
};

Argument::ArgumentValue::ArgumentValue(const Argument::ArgumentValue& other) : __value_str(other.__value_str){};

Argument::ArgumentValue::ArgumentValue(Argument::ArgumentValue&& other) noexcept : __value_str(other.__value_str){};

Argument::ArgumentValue& Argument::ArgumentValue::operator=(const Argument::ArgumentValue& other) {
    if (this != &other) {
        __value_str = other.__value_str;
    }
    return *this;
};

Argument::ArgumentValue& Argument::ArgumentValue::operator=(Argument::ArgumentValue&& other) noexcept {
    if (this != &other) {
        __value_str = other.__value_str;
    }
    return *this;
}

void Argument::ArgumentValue::setValue(char* value_str) {
    if (value_str == NULL) {
        __value_str = std::string("");
    } else {
        __value_str = value_str;
    }
}

void Argument::setValue(char* value_str) {
    __value.setValue(value_str);
}

Argument::Argument() : __name(""), __flag(""), __help(""), __value(NULL) {
}

Argument::Argument(std::string name, std::string flag, std::string help, char* value) : __name(name), __flag(flag), __help(help), __value(value) {
}

Argument::Argument(const Argument& other) : __name(other.__name), __flag(other.__flag), __help(other.__help), __value(other.__value){};

Argument::Argument(Argument&& other) : __name(other.__name), __flag(other.__flag), __help(other.__help), __value(other.__value){};

bool Argument::operator==(const char* other) const {
    return __name == other || __flag == other;
}

bool Argument::operator==(std::string other) const {
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

std::string Argument::ArgumentValue::getValue() const {
    return __value_str;
}

std::string Argument::getName() const {
    return __name;
}

std::string Argument::getFlag() const {
    return __flag;
}

std::string Argument::getValue() const {
    if (__value.getValue().empty()) {
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
                    logger::setw(15) << a.first << "=" <<                                 //
                    logger::setw(15) << (a.second == NULL ? "NULL" : a.second) <<         //
                    " => " <<                                                             //
                    logger::setw(15) << arg.getName() << "[" << arg.getFlag() << "]=" <<  //
                    logger::setw(15) << arg.getValue() << logger::endl;
            }
        }
    }
}

void ArgumentParser::addArgument(Argument&& arg) {
    logger::logger << logger::debug << "Add argument \"" << arg.getName() << "[" << arg.getFlag() << "] -> " << arg.getValue() << "\" to Argument Parser." << logger::endl;
    __arguments.push_back(std::move(arg));
}
