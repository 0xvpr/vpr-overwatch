/**
 * Created by:      VPR
 * Created:         January 17th, 2023
 *
 * Updated by:      VPR
 * Updated:         January 20th, 2023
 *
 * Description:     A file/directory watching utility that executes a specified
 *                  command if the modification time of a file(s) changes.
**/

#include <filesystem>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include <cstdint>
#include <cstdlib>
#include <cerrno>

using filetime_t = std::filesystem::file_time_type;
using nanoseconds_t = std::chrono::nanoseconds;

using std::filesystem::last_write_time;
using std::chrono::time_point_cast;
using std::chrono::steady_clock;

static char*    program;

static auto     frequency_us = nanoseconds_t{static_cast<int>(1E5)};
static int32_t  command_rv;

// TODO: Move to types.hpp
namespace errcodes {
    constexpr int missing_arguments       = -1;
    constexpr int invalid_arguments       = 1;
    constexpr int unsupported_arguments   = 2;
}

namespace flags {
    static char     filepath[256];
    static char     command[256];
    static int      verbose;
    static bool     recurse;
    static bool     no_exec;
}

// TODO: Move to types.hpp
struct Fileinfo {
    using string_t = const char * const __restrict;
    Fileinfo(filetime_t last_write_time, string_t file_path_in)
        : last_modified(last_write_time)
    {
        for (size_t i = 0; (*(relative_file_path+i) = *(file_path_in+i)) && i < sizeof(relative_file_path); ++i);
    }

    filetime_t  last_modified;
    char        relative_file_path[256];
};

[[noreturn]]
auto __usage(const char* const __restrict msg, auto code) -> void {
    std::cerr << "Error message: " << msg << ".\n"
              << "\n"
              << "Usage: " << program << " -f <target_file> -c 'command to execute' [ optional arguments> ]\n"
              << " or \n"
              << "Usage: /path/to/files 'command to execute'\n"
              << "\n"
              << "optional positional arguments:\n"
              << "  path/to/files, command\n"
              << "\n"
              << "required arguments:\n"
              << "  -c\t\tspecify a command to be executed\n"
              << "  -f\t\tspecify a single file to monitor\n"
              << "\n"
              << "optional arguments:\n"
              << "  -n\t\tonly execute the specified command if a modification is detected\n"
              << "  -r\t\trecurse through a given directory\n"
              << "  -t\t\ttime interval in microseconds\n"
              << "  -v\t\tenable minimum verbosity\n"
              << "  -vv\t\tenable increased verbosity\n"
              << "  -vvv\t\tenable maximum verbosity\n"
              << "\n"
              << "example:\n"
              << "  " << program << " . 'clear && echo testing'\n";

    exit(code);
}

auto parse_args(int argc, char** __restrict argv) -> void {
    program = argv[0];

    if (argc < 3) {
        __usage("Positional arguments or explicit flags required", errcodes::missing_arguments);
    }

    if (argc == 3) {
        snprintf(flags::filepath, sizeof(flags::filepath)-1, "%s", argv[1]);
        snprintf(flags::command, sizeof(flags::command)-1, "%s", argv[2]);

        return;
    }

    int i = 1;
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
                            snprintf(flags::command, sizeof(flags::command)-1, "%s", argv[i]+2);
                        } else {
                            snprintf(flags::command, sizeof(flags::command)-1, "%s", argv[i+1]);
                        }
                        break;
                    }
                    case 'f':
                    {
                        if (argv[i][2]) {
                            snprintf(flags::filepath, sizeof(flags::filepath)-1, "%s", argv[i]+2);
                        } else {
                            snprintf(flags::filepath, sizeof(flags::filepath)-1, "%s", argv[i+1]);
                        }
                        break;
                    }
                    case 'n':
                    {
                        flags::no_exec = true;
                        break;
                    }
                    case 'r':
                    {
                        flags::recurse = true;
                        break;
                    }
                    case 't':
                    {
                        uint64_t tmp;
                        if (argv[i][2]) {
                            if (sscanf(argv[i]+2, "%lu", &tmp) != 1) {
                                __usage("Failed to parse argument", errcodes::invalid_arguments);
                            }
                        } else {
                            if (sscanf(argv[i+1], "%lu", &tmp) != 1) {
                                __usage("Failed to parse argument", errcodes::invalid_arguments);
                            }
                            frequency_us = nanoseconds_t{tmp};
                        }
                        break;
                    }
                    case 'v':
                    {
                        flags::verbose = 1;

                        if (argv[i][2] != 0 && argv[i][2] == 'v') {
                            flags::verbose = 2;
                        }
                        if (argv[i][3] != 0 && argv[i][3] == 'v') {
                            flags::verbose = 3;
                        }
                        break;
                    }
                    default:
                    {
                        __usage("Unsupported option", errcodes::unsupported_arguments);
                        break;
                    }
                }
            }
        }
        ++i;
    }
}

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(true);
    parse_args(argc, argv);

    std::vector<Fileinfo> files{};
    if (std::filesystem::is_directory(flags::filepath) && flags::recurse) {
        const std::filesystem::path p(flags::filepath);
        std::filesystem::recursive_directory_iterator it(p);

        for (const auto& file : it) {
            const std::filesystem::path f(file);
            if (std::filesystem::is_regular_file(f)) {
                files.emplace_back(Fileinfo(std::filesystem::last_write_time(f), reinterpret_cast<const char *>(f.filename().c_str())));
            }
        }
    } else if (std::filesystem::is_directory(flags::filepath)) {
        std::filesystem::directory_iterator it(flags::filepath);

        for (const auto& file : it) {
            const std::filesystem::path f(file);

            if (std::filesystem::is_regular_file(f)) {
                files.emplace_back(Fileinfo(std::filesystem::last_write_time(f), reinterpret_cast<const char *>(f.filename().c_str())));
            }
        }
    } else if (std::filesystem::is_regular_file(flags::filepath)) {
        const std::filesystem::path f(flags::filepath);
        files.emplace_back(Fileinfo(std::filesystem::last_write_time(f), flags::filepath));
    } else {
        __usage("Please specify a valid file or directory", 2);
    }

    if (!flags::no_exec && (command_rv = system(flags::command))) {
        return command_rv;
    }

    while (true) {
        auto start_time_us = time_point_cast<nanoseconds_t>(std::chrono::steady_clock::now());

        for (auto& current_file : files) {
            std::filesystem::file_time_type new_time{};
            if (current_file.last_modified < (new_time = last_write_time(current_file.relative_file_path))) {
                current_file.last_modified = new_time;

                //printf("Last modification: %s", ctime(&file_stat.st_mtime)); //TODO: if verbose
                if ((command_rv = system(flags::command))) {
                    return command_rv;
                }
                break;
            }
        }

        auto elapsed_time_us = time_point_cast<nanoseconds_t>(steady_clock::now()) - start_time_us;
        auto remaining_time_us = frequency_us - elapsed_time_us;

        std::this_thread::sleep_for(nanoseconds_t{remaining_time_us > nanoseconds_t{0} ?
                remaining_time_us : nanoseconds_t{static_cast<int>(1E5)}});
    }

    return 0;
}
