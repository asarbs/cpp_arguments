#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <iostream>
#include <string>
#include <optional>
#include <map>
#include "libs/logger/logger.h"

struct VersionInfo {
    int                        major;
    int                        minor;
    int                        patch;
    std::optional<std::string> build;
};

std::ostream& operator<<(std::ostream& o, const VersionInfo& v);

class Argument {
   public:
    class ArgumentValue {
       public:
        ArgumentValue(char* value);
        ArgumentValue(const ArgumentValue& other);
        ArgumentValue(ArgumentValue&& other) noexcept;
        ArgumentValue& operator=(const ArgumentValue& other);
        ArgumentValue& operator=(ArgumentValue&& other) noexcept;

        friend std::ostream&   operator<<(std::ostream& o, const Argument::ArgumentValue& v);
        friend logger::Logger& operator<<(logger::Logger& o, const Argument::ArgumentValue& v);

        void        setValue(char* valueStr);
        std::string getValue() const;

       protected:
       private:
        std::string __value_str;
    };
    Argument();
    Argument(std::string name, std::string flag, std::string help, char* value);
    Argument(const Argument& other);
    Argument(Argument&& other);
    Argument& operator=(const Argument& other) noexcept;
    Argument& operator=(Argument&& other) noexcept;
    bool      operator==(const char* other) const;
    bool      operator==(std::string other) const;

    uint32_t getParamValue() const {
        return 42;
    }
    std::string getName() const;
    std::string getFlag() const;
    std::string getValue() const;
    void        setValue(char* valueStr);

   protected:
   private:
    std::string   __name;
    std::string   __flag;
    std::string   __help;
    ArgumentValue __value;
};

class ArgumentParser {
   public:
    static ArgumentParser& getInstance(const std::string& progName, const VersionInfo& ver);
    void                   addArgument(Argument&& arg);
    template <typename T>
    std::optional<T> getArgument(std::string argName) {
        for (auto& arg : __arguments) {
            if (arg == argName) {
                std::stringstream ss(arg.getValue());
                T                 val;
                if (ss >> val) {
                    return std::optional<T>(val);
                }
            }
        }
        return std::optional<T>();
    }
    std::optional<std::string> getArgument(std::string argName) {
        for (auto& arg : __arguments) {
            if (arg == argName) {
                return arg.getValue();
            }
        }
        return std::optional<std::string>();
    }

    void parse(const int argc, char* argv[]);

   protected:
   private:
    ArgumentParser(const std::string& progName, const VersionInfo& version);  // Private constructor - prevents creating objects outside the class
    ArgumentParser(const ArgumentParser&)            = delete;                // Remove the ability to copy and assign
    ArgumentParser(ArgumentParser&&)                 = delete;                // Remove the ability to move
    ArgumentParser& operator=(const ArgumentParser&) = delete;                // Remove the ability to copy and assign
    ArgumentParser& operator=(ArgumentParser&&)      = delete;                // Remove the ability to move

    std::string __prog_name;
    VersionInfo __version;

    std::vector<Argument> __arguments;
};

#endif  // ARGUMENTS_H_
