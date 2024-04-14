#include <filesystem>

#include "watcher.hpp"
#include "parser.hpp"
#include "types.hpp"

using std::filesystem::last_write_time;

void watch_files(std::vector<types::file_info_t>& files, const types::parsed_args_t& parsed_args) {
    int subcommand_rv = 0;

    for (auto& current_file : files) {
        types::filetime_t new_time{};

        try {
            if (current_file.last_modified < (new_time = last_write_time(current_file.filepath))) {
                current_file.last_modified = new_time;

                //printf("Last modification: %s", ctime(&file_stat.st_mtime)); //TODO: if verbose
                if ((subcommand_rv = system(parsed_args.command.c_str()))) {
                    // TODO log err
                }
                break;
            }
        } catch (...) {
            // TODO handle the [] bullshit
        }
    }
}
