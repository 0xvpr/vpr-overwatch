#include <filesystem>

#include "watcher.hpp"
#include "parser.hpp"
#include "types.hpp"

using std::filesystem::last_write_time;

void watch_files(std::vector<types::fileinfo_t>& files, const types::parsedargs_t& parsedArgs) {
    int subcommand_rv{};
    for (auto& current_file : files) {
        std::filesystem::file_time_type new_time{};
        try {
            if (current_file.last_modified < (new_time = last_write_time(current_file.relative_file_path))) {
                current_file.last_modified = new_time;

                //printf("Last modification: %s", ctime(&file_stat.st_mtime)); //TODO: if verbose
                if ((subcommand_rv = system(parsedArgs.command))) {
                    // TODO log err
                }
                break;
            }
        } catch (...) {
            // TODO handle the [] bullshit
        }
    }
}
