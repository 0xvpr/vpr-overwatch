#include <iostream>
#include <cstdio>
#include <cmath>

#include "constants.hpp"
#include "parser.hpp"
#include "types.hpp"
#include "util.hpp"

parser::parser(int argc, char** argv, types::err_t& err) noexcept
  : parsed_args_{
    .initial_exec = false,
    .recursive = false,
    .verbosity = 0,
    .frequency_us{ types::microseconds_t{constants::default_frequency_us} },
    .command{ },
    .program_name{ argv[0] },
    .filepaths{ }
  }
{
    if (argc < 3) {
        err.code = types::missing_arguments;
        err.msg = types::error_messages[err.code];

        return;
    }

    if (argc == 3) {
        parsed_args_.filepaths.emplace_back(argv[1]);
        parsed_args_.command = argv[2];

        return;
    }

    types::errcodes error_code = types::errcodes::no_error;
    for (int arg_index = 1; arg_index < argc; ++arg_index) {
        std::string arg(argv[arg_index]);

        if (arg[0] == '-') {
            if ( (arg_index+1 < argc) && (argv[arg_index+1][0] != '-') ) {
                error_code = parse_option(arg, argv[++arg_index]);
            } else {
                error_code = set_flag(arg);
            }
        } else {
            parsed_args_.filepaths.emplace_back(arg);
        }

        if (error_code) {
            err.code = error_code;
            err.msg = types::error_messages[error_code];

            return;
        }
    }
}

types::errcodes parser::set_flag(const std::string& flag) noexcept {
    if (flag == "-i") {
        parsed_args_.initial_exec = true;
    } else if (flag == "-r") {
        parsed_args_.recursive = true;
    } else if (flag == "-v") {
        parsed_args_.verbosity = 1;
    } else if (flag == "-vv") {
        parsed_args_.verbosity = 2;
    } else if (flag == "-vvv") {
        parsed_args_.verbosity = 3;
    } 

    return types::errcodes::unsupported_arguments;
}

types::errcodes parser::parse_option(const std::string& option, const std::string& value) noexcept {
    if (option == "-c") {
        parsed_args_.command = value;
    } else if (option == "-f") {
        std::uint64_t us{};

#if defined(__clang__) && defined(__apple_build_version__) // alternatively, check for xclang libcpp
        int success = std::sscanf(value.c_str(),"%lu", &us);
        if (success != 1) {
            return types::errcodes::invalid_arguments;
        }
#else // but for everyone else, apparently...
        std::istringstream iss(value);
        iss >> us;
        if (iss.fail()) {
            return types::errcodes::invalid_arguments;
        }
#endif // defined(__clang__) && defined(__apple_build_version__)
        parsed_args_.frequency_us = types::microseconds_t(us);
    } 

    return types::errcodes::unsupported_arguments;
}
