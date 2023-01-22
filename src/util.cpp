#include <iostream>

#include "util.hpp"

void util::usage(const char * const __restrict program, const char* const __restrict msg, auto code) {
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

std::vector<types::fileinfo_t> util::get_files(const types::parsedargs_t& parsedArgs) {
    std::vector<types::fileinfo_t> files{};

    if (std::filesystem::is_directory(parsedArgs.filepath) && parsedArgs.recursive) {
        const std::filesystem::path p(parsedArgs.filepath);
        std::filesystem::recursive_directory_iterator it(p);

        for (const auto& file : it) {
            const std::filesystem::path f(file);

            try {
                if (std::filesystem::is_regular_file(f)) {
                    auto const relative_path = std::move(f.string().c_str());
                    files.emplace_back(types::fileinfo_t(std::filesystem::last_write_time(f), relative_path));
                }
            } catch (...) {
                // TODO log error
            }
        }
    } else if (std::filesystem::is_directory(parsedArgs.filepath)) {
        std::filesystem::directory_iterator it(parsedArgs.filepath);

        for (const auto& file : it) {
            const std::filesystem::path f(file);

            try {
                if (std::filesystem::is_regular_file(f)) {
                    auto const relative_path = std::move(f.string().c_str());
                    files.emplace_back(types::fileinfo_t(std::filesystem::last_write_time(f), relative_path));
                }
            } catch (...) {
                // TODO log error
            }
        }
    } else if (std::filesystem::is_regular_file(parsedArgs.filepath)) {
        const std::filesystem::path f(parsedArgs.filepath);
        
        try {
            files.emplace_back(types::fileinfo_t(std::filesystem::last_write_time(f), parsedArgs.filepath));
        } catch (...) {
            // TODO log error
        }
    } else {
        util::usage(parsedArgs.program_name, "Please specify a valid file or directory", 2);
    }

    return files;
}
