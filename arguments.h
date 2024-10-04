#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <iostream>
#include <string>
#include <optional>
#include <map>

struct VersionInfo {
    int                        major;
    int                        minor;
    int                        patch;
    std::optional<std::string> build;
};

template <class T>
class Argument {
   public:
    Argument();

    // Remove the ability to copy and assign
    Argument<T>(const Argument<T>&)            = delete;
    Argument<T>& operator=(const Argument<T>&) = delete;

    // Remove the ability to move
    Argument<T>(Argument<T>&&)            = delete;
    Argument<T>& operator=(Argument<T>&&) = delete;

    T getParamValue();

   protected:
   private:
    T __param;
};

std::ostream& operator<<(std::ostream& o, const VersionInfo& v);

class ArgumentParser {
   public:
    static ArgumentParser& getInstance(int argc, char* argv[], const std::string& prog_name, const VersionInfo& ver);
    void                   addArgument(const Argument& arg);

   protected:
   private:
    // Private constructor - prevents creating objects outside the class
    ArgumentParser(const std::string& prog_name, const VersionInfo& version);

    // Remove the ability to copy and assign
    ArgumentParser(const ArgumentParser&)            = delete;
    ArgumentParser& operator=(const ArgumentParser&) = delete;

    // Remove the ability to move
    ArgumentParser(ArgumentParser&&)            = delete;
    ArgumentParser& operator=(ArgumentParser&&) = delete;

    std::string __prog_name;
    VersionInfo __version;

    std::map<std::string, Argument> __arguments;
};

#endif  // ARGUMENTS_H_
