#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <iostream>
#include <map>
#include <optional>
#include <string>

#include "logger.h"

namespace Argument {
    struct VersionInfo {
        int major;
        int minor;
        int patch;
        std::optional<std::string> build;
    };

    enum class Action {
        Store,
        StoreBool,
        Help,
        Version,
    };

    class Argument {
       public:
        class ArgumentValue {
           public:
            ArgumentValue(std::string value);
            ArgumentValue(const ArgumentValue& other);
            ArgumentValue(ArgumentValue&& other) noexcept;
            ArgumentValue& operator=(const ArgumentValue& other);
            ArgumentValue& operator=(ArgumentValue&& other) noexcept;

            friend logger::Logger& operator<<(logger::Logger& o, const Argument::ArgumentValue& v);

            void setValue(std::string valueStr);
            std::string getValue() const;

           protected:
           private:
            std::string __value_str;
        };
        Argument();
        Argument(std::string name, Action action, std::string flag, std::string help, std::string value);
        Argument(std::string name, Action action, std::string flag, std::string help, std::string value, std::vector<std::string> valueList);
        Argument(const Argument& other);
        Argument(Argument&& other);
        Argument& operator=(const Argument& other) noexcept;
        Argument& operator=(Argument&& other) noexcept;

        friend std::ostream& operator<<(std::ostream& o, const Argument& v);

        // ~Argument();
        bool operator==(const char* other) const;
        bool operator==(std::string other) const;

        std::string getName() const;
        std::string getFlag() const;
        std::string getHelp() const;
        std::string getValue() const;
        std::vector<std::string> getValueList() const;
        void setValue(std::string valueStr);
        Action getAction() const;
        virtual bool validate() const;

       protected:
       private:
        std::string __name;
        Action __action;
        std::string __flag;
        std::string __help;
        ArgumentValue __value;
        std::vector<std::string> __valueList;
        bool __hadValue;
    };

    class ArgumentStore : public Argument {
       public:
        ArgumentStore(std::string name, Action action, std::string flag, std::string help, std::string value);
        ArgumentStore(std::string name, Action action, std::string flag, std::string help, std::string value, std::vector<std::string> valueList);

       protected:
       private:
    };
    class ArgumentStoreBool : public Argument {
       public:
        ArgumentStoreBool(std::string name, Action action, std::string flag, std::string help, std::string value);
        ArgumentStoreBool(std::string name, Action action, std::string flag, std::string help, std::string value, std::vector<std::string> valueList);
       protected:
       private:
    };
    class ArgumentHelp : public Argument {
       public:
        ArgumentHelp(std::string name, Action action, std::string flag, std::string help);

       protected:
       private:
    };
    class ArgumentVersion : public Argument {
       public:
        ArgumentVersion(std::string name, Action action, std::string flag, std::string help);

       protected:
       private:
    };

    class ArgumentParser {
       public:
        static ArgumentParser& getInstance(const std::string& progName, const VersionInfo& ver);
        void addArgument(std::string name, Action action, std::string flag, std::string help, std::string value);
        void addArgument(std::string name, Action action, std::string flag, std::string help, std::string value, std::vector<std::string> valueList);

        template <typename T>
        std::optional<T> getArgument(std::string argName) {
            for (Argument* p_arg : __arguments) {
                if ((*p_arg) == argName) {
                    if (!p_arg->validate()) {
                        return std::optional<T>();
                    }
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

        template <>
        std::optional<bool> getArgument<bool>(std::string argName) {
            for (Argument* p_arg : __arguments) {
                if ((*p_arg) == argName) {
                    if (!p_arg->validate()) {
                        return std::optional<bool>();
                    }
                    if(p_arg->getAction() == Action::StoreBool ){
                        if( p_arg->getValue() == "true") {
                            return std::optional<bool>(true);
                        } else {
                            return std::optional<bool>(false);
                        }
                    } 
                }
            }
            return std::optional<bool>();
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
        void reset();

       protected:
       private:
        ArgumentParser(const std::string& progName,
                       const VersionInfo& version);                 // Private constructor - prevents
                                                                    // creating objects outside the class
        ArgumentParser(const ArgumentParser&) = delete;             // Remove the ability to copy and assign
        ArgumentParser(ArgumentParser&&) = delete;                  // Remove the ability to move
        ArgumentParser& operator=(const ArgumentParser&) = delete;  // Remove the ability to copy and assign
        ArgumentParser& operator=(ArgumentParser&&) = delete;       // Remove the ability to move
        Argument* __buildArgument(std::string name, Action action, std::string flag, std::string help, std::string value, std::vector<std::string> valueList);
        void __printVersion();
        void __printHelp();

        std::string __prog_name;
        VersionInfo __version;

        std::vector<Argument*> __arguments;
    };

    std::ostream& operator<<(std::ostream& o, const VersionInfo& v);
    std::ostream& operator<<(std::ostream& o, const Argument& v);
    logger::Logger& operator<<(logger::Logger& o, const Action& a);
    logger::Logger& operator<<(logger::Logger& o, const Argument::ArgumentValue& v);

};      // namespace Argument
#endif  // ARGUMENTS_H_
