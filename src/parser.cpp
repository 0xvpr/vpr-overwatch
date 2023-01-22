#include <iostream>
#include <cstdio>

#include "parser.hpp"
#include "types.hpp"
#include "util.hpp"

types::parsedargs_t parse_args(int argc, char** __restrict argv) {
    types::parsedargs_t parsedArgs{};
    for (unsigned i = 0; (*parsedArgs.program_name = *(argv[0]+i)) && i < sizeof(parsedArgs.program_name); ++i);

    if (argc < 3) {
        util::usage(parsedArgs.program_name, "Positional arguments or explicit parser_flags required", types::errcodes::missing_arguments);
    }

    auto i = [&argv, &parsedArgs]() -> int {
        if (argv[1][0] != '-' && argv[2][0] != '-') {
            snprintf(parsedArgs.filepath, sizeof(parsedArgs.filepath)-1, "%s", argv[1]);
            snprintf(parsedArgs.command, sizeof(parsedArgs.command)-1, "%s", argv[2]);

            return 3;
        } else {
            return 1;
        }
    }();

    while (i < argc) {
        switch (argv[i][0])
        {
            case '-':
            {
                switch (argv[i][1])
                {
                    case 'c':
                    {
                        if (argv[i][2]) {
                            snprintf(parsedArgs.command, sizeof(parsedArgs.command)-1, "%s", argv[i]+2);
                        } else {
                            snprintf(parsedArgs.command, sizeof(parsedArgs.command)-1, "%s", argv[i+1]);
                        }
                        break;
                    }
                    case 'f':
                    {
                        if (argv[i][2]) {
                            snprintf(parsedArgs.filepath, sizeof(parsedArgs.filepath)-1, "%s", argv[i]+2);
                        } else {
                            snprintf(parsedArgs.filepath, sizeof(parsedArgs.filepath)-1, "%s", argv[i+1]);
                        }
                        break;
                    }
                    case 'n':
                    {
                        parsedArgs.no_initial_exec = true;
                        break;
                    }
                    case 'r':
                    {
                        parsedArgs.recursive = true;
                        break;
                    }
                    case 't':
                    {
                        uint64_t tmp;
                        if (argv[i][2]) {
                            if (sscanf(argv[i]+2, "%lu", &tmp) != 1) {
                                util::usage(parsedArgs.program_name, "Failed to parse argument", types::errcodes::invalid_arguments);
                            }
                        } else {
                            if (sscanf(argv[i+1], "%lu", &tmp) != 1) {
                                util::usage(parsedArgs.program_name, "Failed to parse argument", types::errcodes::invalid_arguments);
                            }
                            parsedArgs.frequency_us = types::nanoseconds_t{tmp};
                        }
                        break;
                    }
                    case 'v':
                    {
                        parsedArgs.verbosity = 1;

                        if (argv[i][2] != 0 && argv[i][2] == 'v') {
                            parsedArgs.verbosity = 2;
                        }
                        if (argv[i][3] != 0 && argv[i][3] == 'v') {
                            parsedArgs.verbosity = 3;
                        }
                        break;
                    }
                    default:
                    {
                        util::usage(parsedArgs.program_name, "Unsupported option", types::errcodes::unsupported_arguments);
                        break;
                    }
                }
            }
        }
        ++i;
    }

    return parsedArgs;
}
