#include <iostream>

#include "types.hpp"
#include "util.hpp"

void util::usage(const char * const __restrict program, const char* const __restrict msg, types::errcodes code) {
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

void util::usage(const char * const __restrict program, const types::err_t& err) {
    std::cerr << "Error message: " << err.msg << ".\n"
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

    exit(err.code);
}

std::vector<types::file_info_t> util::get_files(const types::parsed_args_t& parsed_args) {
    std::vector<types::file_info_t> files{};
    if (parsed_args.recursive) {
        files.reserve(2048);
    }

    for (const auto& filepath : parsed_args.filepaths) {
        if (std::filesystem::is_directory(filepath) && parsed_args.recursive) {
            const std::filesystem::path p(filepath);
            std::filesystem::recursive_directory_iterator it(p);

            for (const auto& file : it) {
                const std::filesystem::path f(file);

                try {
                    if (std::filesystem::is_regular_file(f)) {
                        //auto const relative_path = std::move(f.string());
                        files.emplace_back(std::filesystem::last_write_time(f), f.string());
                    }
                } catch (...) {
                    // TODO log error
                }
            }
        } else if (std::filesystem::is_directory(filepath)) {
            std::filesystem::directory_iterator it(filepath);

            for (const auto& file : it) {
                const std::filesystem::path f(file);

                try {
                    if (std::filesystem::is_regular_file(f)) {
                        //auto const relative_path = std::move(f.string());
                        files.emplace_back(std::filesystem::last_write_time(f), f.string());
                    }
                } catch (...) {
                    // TODO log error
                }
            }
        } else if (std::filesystem::is_regular_file(filepath)) {
            const std::filesystem::path f(filepath);
            
            try {
                files.emplace_back(std::filesystem::last_write_time(f), f.string());
            } catch (...) {
                // TODO log error
            }
        } else {
            util::usage(parsed_args.program_name.c_str(), "Please specify a valid file or directory", types::errcodes::invalid_arguments);
        }
    }

    return files;
}
