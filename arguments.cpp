#include "arguments.h"

#include "logger.h"

std::ostream& operator<<(std::ostream& o, const Argument::VersionInfo& v) {
    o << v.major << "." << v.minor << "." << v.patch;
    if (v.build) {
        o << " (" << *v.build << ")";
    }

    return o;
}

logger::Logger& Argument::operator<<(logger::Logger& o, const Action& a) {
    switch (a) {
        case Action::Store:
            o << "Store";
            break;
        case Action::StoreTrue:
            o << "StoreTrue";
            break;
        case Action::StoreFalse:
            o << "StoreFalse";
            break;
        case Action::Help:
            o << "Help";
            break;
        case Action::Version:
            o << "Version";
            break;
        default:
            o << "Unknown Action";
    }
    return o;
}

logger::Logger& Argument::operator<<(logger::Logger& o, const Argument::Argument::ArgumentValue& v) {
    o << v.__value_str;
    return o;
}

Argument::Argument::ArgumentValue::ArgumentValue(char* value) {
    if (value == NULL) {
        __value_str = "";
    } else {
        __value_str = value;
    }
};

Argument::Argument::ArgumentValue::ArgumentValue(const Argument::Argument::ArgumentValue& other)
    : __value_str(other.__value_str){
          // logger::logger << logger::debug << "ArgumentValue::ArgumentValue(const Argument::Argument::ArgumentValue& other)=" << __value_str << "=" << other.__value_str << ";"
          // << logger::endl;
      };

Argument::Argument::ArgumentValue::ArgumentValue(Argument::Argument::ArgumentValue&& other) noexcept
    : __value_str(other.__value_str){
          // logger::logger << logger::debug << "ArgumentValue::ArgumentValue(Argument::Argument::ArgumentValue&& other)=" << __value_str << ";" << logger::endl;
      };

Argument::Argument::ArgumentValue& Argument::Argument::ArgumentValue::operator=(const Argument::Argument::ArgumentValue& other) {
    if (this != &other) {
        __value_str = other.__value_str;
    }
    return *this;
};

Argument::Argument::ArgumentValue& Argument::Argument::ArgumentValue::operator=(Argument::Argument::ArgumentValue&& other) noexcept {
    if (this != &other) {
        __value_str = other.__value_str;
    }
    return *this;
}

void Argument::Argument::ArgumentValue::setValue(char* value_str) {
    if (value_str == NULL) {
        __value_str = std::string("");
    } else {
        __value_str = value_str;
    }
    // logger::logger << logger::debug << "ArgumentValue::setValue=" << __value_str << ";" << logger::endl;
}

void Argument::Argument::setValue(char* value_str) {
    __value.setValue(value_str);
    __hadValue = true;
    // logger::logger << logger::debug << this << "; Argument::setValue=" << __value << "=" << (value_str == NULL ? "NULL" : value_str) << ";" << logger::endl;
}

Argument::Action Argument::Argument::getAction() const { return __action; }

Argument::Argument::Argument() : __name(""), __action(Action::Store), __flag(""), __help(""), __value(NULL), __hadValue(false) {
    // logger::logger << logger::debug << "Argument::Argument::Argument()" << logger::endl;
}

Argument::Argument::Argument(std::string name, Action action, std::string flag, std::string help, char* value)
    : __name(name), __action(action), __flag(flag), __help(help), __value(value) {
    // logger::logger << logger::debug <<  //
    //     "Create Argument: name=\"" << __name
    //                << "\", "  //
    //                   "flag=\""
    //                << __flag
    //                << "\", "  //
    //                   "action=\""
    //                << __action
    //                << "\", "  //
    //                   "value=\""
    //                << __value
    //                << "\", "  //
    //                   "help=\""
    //                << __help << "\";"  //
    //                << this << ";" << logger::endl;
}

Argument::Argument::Argument(const Argument& other)
    : __name(other.__name), __action(other.__action), __flag(other.__flag), __help(other.__help),
      __value(other.__value){
          // logger::logger << logger::debug << this << ":" << &other << "; Argument::Argument(const Argument& other)=" << __value << "=" << other.__value << ";" << logger::endl;
      };

Argument::Argument::Argument(Argument&& other) : __name(other.__name), __action(other.__action), __flag(other.__flag), __help(other.__help), __value(other.__value){};

bool Argument::Argument::operator==(const char* other) const { return __name == other || __flag == other; }

bool Argument::Argument::operator==(std::string other) const { return __name == other || __flag == other; }

Argument::Argument& Argument::Argument::operator=(const Argument& other) noexcept {
    __name = other.__name;
    __flag = other.__flag;
    __help = other.__help;
    __value = other.__value;
    __action = other.__action;
    return *this;
};

Argument::Argument& Argument::Argument::operator=(Argument&& other) noexcept {
    __name = other.__name;
    __flag = other.__flag;
    __help = other.__help;
    __value = other.__value;
    return *this;
};

std::string Argument::Argument::ArgumentValue::getValue() const { return __value_str; }

std::string Argument::Argument::getName() const { return __name; }

std::string Argument::Argument::getFlag() const { return __flag; }

std::string Argument::Argument::getHelp() const { return __help; }

std::string Argument::Argument::getValue() const {
    if (__value.getValue().empty()) {
        return std::string("NULL");
    }
    return std::string(__value.getValue());
}

Argument::ArgumentStore::ArgumentStore(std::string name, Action action, std::string flag, std::string help, char* value) : Argument(name, action, flag, help, value) {}

Argument::ArgumentStoreBool::ArgumentStoreBool(std::string name, Action action, std::string flag, std::string help, char* value) : Argument(name, action, flag, help, value) {}

Argument::ArgumentHelp::ArgumentHelp(std::string name, Action action, std::string flag, std::string help, char* value) : Argument(name, action, flag, help, value) {}

Argument::ArgumentVersion::ArgumentVersion(std::string name, Action action, std::string flag, std::string help, char* value) : Argument(name, action, flag, help, value) {}

Argument::ArgumentParser::ArgumentParser(const std::string& prog_name, const VersionInfo& version) : __prog_name(prog_name), __version(version) {}

Argument::ArgumentParser& Argument::ArgumentParser::getInstance(const std::string& prog_name, const VersionInfo& ver) {
    static ArgumentParser instance(prog_name, ver);
    return instance;
}

void Argument::ArgumentParser::parse(const int argc, char* argv[]) {
    addArgument("--version", Action::Version, "-v", "show program's version number and exit", NULL);
    addArgument("--help", Action::Help, "-h", "show this help message and exit", NULL);

    std::vector<std::pair<char*, char*>> mainArgs;
    const char constant = '-';

    for (uint32_t argIndex = 1; argIndex < argc; argIndex++) {
        if (argv[argIndex][0] == constant) {
            mainArgs.push_back({argv[argIndex], NULL});

        } else {
            mainArgs.back().second = argv[argIndex];
        }
    }

    for (const auto& a : mainArgs) {
        for (Argument* p_arg : __arguments) {
            if ((*p_arg) == a.first) {
                p_arg->setValue(a.second);

                if (p_arg->getAction() == Action::Version) {
                    __printVersion();
                }
                if (p_arg->getAction() == Action::Help) {
                    __printHelp();
                }

                logger::logger << logger::debug << "update argument value:" <<                  //
                    logger::setw(10) << a.first << "=" <<                                       //
                    logger::setw(10) << (a.second == NULL ? "NULL" : a.second) <<               //
                    " => " <<                                                                   //
                    logger::setw(10) << p_arg->getName() << "[" << p_arg->getFlag() << "]=" <<  //
                    logger::setw(10) << p_arg->getValue() << " < " << p_arg->getAction()        //
                               << "; "                                                          //
                               << p_arg << ";" << logger::endl;
            }
        }
    }
}

Argument::Argument* Argument::ArgumentParser::__buildArgument(std::string name, Action action, std::string flag, std::string help, char* value) {
    switch (action) {
        case Action::Store:
            return new ArgumentStore(name, action, flag, help, value);
        case Action::StoreTrue:
            return new ArgumentStoreBool(name, action, flag, help, value);
        case Action::StoreFalse:
            return new ArgumentStoreBool(name, action, flag, help, value);
        case Action::Help:
            return new ArgumentHelp(name, action, flag, help, value);
        case Action::Version:
            return new ArgumentVersion(name, action, flag, help, value);
        default:
            return NULL;
    }
}

void Argument::ArgumentParser::addArgument(std::string name, Action action, std::string flag, std::string help, char* value) {
    Argument* newArg = __buildArgument(name, action, flag, help, value);
    if (newArg != nullptr) {
        __arguments.push_back(newArg);
    } else {
        logger::logger << logger::error << "Argument \"" << name << "\" was not created." << logger::endl;
    }
}

void Argument::ArgumentParser::__printVersion() {
    std::cout << __prog_name << " " << __version.major << "." << __version.minor << "." << __version.patch;
    if (__version.build.has_value()) {
        std::cout << ":" << __version.build.value();
    }
    std::cout << std::endl;
    exit(0);
}

void Argument::ArgumentParser::__printHelp() {
    std::cout << "usage: " << __prog_name;
    for (Argument* p_arg : __arguments) {
        std::cout << " [" << p_arg->getFlag() << "]";
    }

    std::cout << std::endl;
    std::cout << "options:" << std::endl;
    for (Argument* p_arg : __arguments) {
        std::cout << std::setw(5) << p_arg->getFlag() << ", " << std::setw(15) << std::left << p_arg->getName() << std::right << p_arg->getHelp() << std::endl;
    }
    exit(0);
}