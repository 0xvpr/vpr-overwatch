#include <filesystem>
#include <iostream>

#include "types.hpp"
#include "util.hpp"

namespace fs = std::filesystem;

void util::usage(const char * const __restrict program, const char* const __restrict msg, types::errcodes code) {
    std::cerr << "Error message: " << msg << "\n"
              << "\n"
              << "Usage: " << program << " /path/to/file1 /path/to/fileN -c 'command to execute' [ <optional arguments> ]\n"
              << " or \n"
              << "Usage: " << program << " /path/to/file 'command to execute'\n"
              << "\n"
              << "optional positional arguments:\n"
              << "  /path/to/file(s), 'command'\n"
              << "\n"
              << "required arguments:\n"
              << "  -c\t\tspecify a command to be executed\n"
              << "  -f\t\tspecify a single file to monitor\n"
              << "\n"
              << "optional arguments:\n"
              << "  -i\t\texecute at least once initially, before modification is detected\n"
              << "  -r\t\trecurse through a given directory\n"
              << "  -f\t\tspecify frequency in microseconds\n"
              << "  -v\t\tenable minimum verbosity\n"
              << "  -vv\t\tenable increased verbosity\n"
              << "  -vvv\t\tenable maximum verbosity\n"
              << "\n"
              << "example:\n"
              << "  " << program << " . 'clear && echo testing'\n";

    exit(code);
}

void util::usage(const char * const __restrict program, const types::err_t& err) {
    std::cerr << "Error message: " << err.msg << "\n"
              << "\n"
              << "Usage: " << program << " /path/to/file1 /path/to/fileN -c 'command to execute' [ <optional arguments> ]\n"
              << " or \n"
              << "Usage: " << program << " /path/to/file 'command to execute'\n"
              << "\n"
              << "optional positional arguments:\n"
              << "  /path/to/file(s), 'command'\n"
              << "\n"
              << "required arguments:\n"
              << "  -c\t\tspecify a command to be executed\n"
              << "  -f\t\tspecify a single file to monitor\n"
              << "\n"
              << "optional arguments:\n"
              << "  -i\t\texecute at least once initially, before modification is detected\n"
              << "  -r\t\trecurse through a given directory\n"
              << "  -f\t\tspecify frequency in microseconds\n"
              << "  -v\t\tenable minimum verbosity\n"
              << "  -vv\t\tenable increased verbosity\n"
              << "  -vvv\t\tenable maximum verbosity\n"
              << "\n"
              << "example:\n"
              << "  " << program << " . 'clear && echo testing'\n";

    exit(err.code);
}

std::vector<types::file_info_t> util::get_files(const types::parsed_args_t& parsed_args) {
    std::vector<types::file_info_t> files{};
    files.reserve(2048);

    for (const auto& filepath : parsed_args.filepaths) {
        if (fs::is_directory(filepath) && parsed_args.recursive) {
            const fs::path p(filepath);
            fs::recursive_directory_iterator it(p);
            if ( !(it->exists()) ) {
                continue;
            }

            for (const auto& file : it) {
                const fs::path f(file);

                if (fs::is_regular_file(f)) {
                    files.emplace_back(types::file_info_t{fs::last_write_time(f), f.string()});
                }
            }
        } else if (fs::is_directory(filepath)) {
            fs::directory_iterator it(filepath);

            for (const auto& file : it) {
                const fs::path f(file);

                if (fs::is_regular_file(f)) {
                    files.emplace_back(types::file_info_t{fs::last_write_time(f), f.string()});
                }
            }
        } else if (fs::is_regular_file(filepath)) {
            const fs::path f(filepath);
            
            files.emplace_back(types::file_info_t{fs::last_write_time(f), f.string()});
        } else {
            util::usage(parsed_args.program_name.c_str(), "Please specify a valid file or directory", types::errcodes::invalid_arguments);
        }
    }

    return files;
}
