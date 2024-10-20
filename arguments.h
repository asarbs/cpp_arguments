#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <iostream>
#include <map>
#include <optional>
#include <string>

#include "libs/logger/logger.h"

namespace Argument {
    struct VersionInfo {
        int major;
        int minor;
        int patch;
        std::optional<std::string> build;
    };

    enum class Action {
        Store,
        StoreTrue,
        StoreFalse,
        Help,
        Version,
    };

    class Argument {
       public:
        class ArgumentValue {
           public:
            ArgumentValue(char* value);
            ArgumentValue(const ArgumentValue& other);
            ArgumentValue(ArgumentValue&& other) noexcept;
            ArgumentValue& operator=(const ArgumentValue& other);
            ArgumentValue& operator=(ArgumentValue&& other) noexcept;

            friend logger::Logger& operator<<(logger::Logger& o, const Argument::ArgumentValue& v);

            void setValue(char* valueStr);
            std::string getValue() const;

           protected:
           private:
            std::string __value_str;
        };
        Argument();
        Argument(std::string name, Action action, std::string flag, std::string help, char* value);
        Argument(const Argument& other);
        Argument(Argument&& other);
        Argument& operator=(const Argument& other) noexcept;
        Argument& operator=(Argument&& other) noexcept;
        // ~Argument();
        bool operator==(const char* other) const;
        bool operator==(std::string other) const;

        uint32_t getParamValue() const { return 42; }
        std::string getName() const;
        std::string getFlag() const;
        std::string getValue() const;
        void setValue(char* valueStr);

       protected:
       private:
        std::string __name;
        Action __action;
        std::string __flag;
        std::string __help;
        ArgumentValue __value;
    };

    class ArgumentStore : public Argument {
       public:
        ArgumentStore(std::string name, Action action, std::string flag, std::string help, char* value);

       protected:
       private:
    };
    class ArgumentStoreBool : public Argument {
       public:
        ArgumentStoreBool(std::string name, Action action, std::string flag, std::string help, char* value);

       protected:
       private:
    };
    class ArgumentHelp : public Argument {
       public:
        ArgumentHelp(std::string name, Action action, std::string flag, std::string help, char* value);

       protected:
       private:
    };
    class ArgumentVersion : public Argument {
       public:
        ArgumentVersion(std::string name, Action action, std::string flag, std::string help, char* value);

       protected:
       private:
    };

    class ArgumentParser {
       public:
        static ArgumentParser& getInstance(const std::string& progName, const VersionInfo& ver);
        void addArgument(std::string name, Action action, std::string flag, std::string help, char* value);

        template <typename T>
        std::optional<T> getArgument(std::string argName) {
            for (Argument* p_arg : __arguments) {
                if ((*p_arg) == argName) {
                    // logger::logger << logger::debug << arg.getName() << ":" << argName << ":" << p_arg->getName() << ":" << arg.getValue() << ":" << p_arg->getValue() << ";"
                    //                << p_arg << logger::endl;
                    std::stringstream ss(p_arg->getValue());
                    T val;
                    if (ss >> val) {
                        return std::optional<T>(val);
                    } else {
                        logger::logger << logger::warning << "Can't get vale of \"" << p_arg->getName() << "\"." << logger::endl;
                    }
                }
            }
            return std::optional<T>();
        }
        std::optional<std::string> getArgument(std::string argName) {
            for (Argument* p_arg : __arguments) {
                if ((*p_arg) == argName) {
                    return p_arg->getValue();
                }
            }
            return std::optional<std::string>();
        }

        void parse(const int argc, char* argv[]);

       protected:
       private:
        ArgumentParser(const std::string& progName,
                       const VersionInfo& version);                 // Private constructor - prevents creating
                                                                    // objects outside the class
        ArgumentParser(const ArgumentParser&) = delete;             // Remove the ability to copy and assign
        ArgumentParser(ArgumentParser&&) = delete;                  // Remove the ability to move
        ArgumentParser& operator=(const ArgumentParser&) = delete;  // Remove the ability to copy and assign
        ArgumentParser& operator=(ArgumentParser&&) = delete;       // Remove the ability to move
        Argument* __buildArgument(std::string name, Action action, std::string flag, std::string help, char* value);
        std::string __prog_name;
        VersionInfo __version;

        std::vector<Argument*> __arguments;
    };

    std::ostream& operator<<(std::ostream& o, const VersionInfo& v);
    logger::Logger& operator<<(logger::Logger& o, const Action& a);
    logger::Logger& operator<<(logger::Logger& o, const Argument::ArgumentValue& v);

};      // namespace Argument
#endif  // ARGUMENTS_H_
