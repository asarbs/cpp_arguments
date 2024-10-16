# Arguments Utility

Cpp Arguments is a C++ library for managing command-line arguments. It allows easy parsing and manipulation of arguments, as well as storing values in an organized manner.

## Documentation
API documentation is available in the header files and documents in the repository. We encourage you to refer to the source code for a better understanding of how to use the library.

## Contributing
All contributions are welcome! If you would like to make improvements, please fork the repository and submit a pull request.

## Files

- `arguments.h`: Header file defining the arguments class and its functionalities.

## Usage

### Installation

To use the arguments in your project, simply include the header files and compile the source file along with your project.


## Basic Example
```cpp
int main(int argc, char* argv[]) {
    logger::logger.setLogLevel(logger::debug);

    ArgumentParser& argpars = ArgumentParser::getInstance(argc, argv, "test app", {12, 13, 4, "a0e67de04e79"});
    char*           val     = (char*)"-1";
    argpars.addArgument({"--test_a", "-a", "help str0", Argument::Type::uint8, val});
    argpars.addArgument({"--test_b", "-b", "help str1", Argument::Type::uint8, val});
    argpars.addArgument({"--test_c", "-c", "help str2", Argument::Type::uint8, val});
    argpars.addArgument({"--test_d", "-d", "help str2", Argument::Type::uint8, val});
    argpars.addArgument({"--test_e", "-e", "help str2", Argument::Type::uint8, val});

    (void)(argpars);

    return 0;
}


```

### Run Example
type
```shell
$ make run
```
![console output](doc/output.png)
</div>


