#include <filesystem>

#include "watcher.hpp"
#include "parser.hpp"
#include "types.hpp"

namespace fs = std::filesystem;

int watch_files(std::vector<types::file_info_t>& files, const types::parsed_args_t& parsed_args) {
    (void)parsed_args; // add args for additional watch options

    for (auto& current_file : files) {
        if ( !fs::exists(current_file.filepath) || current_file.filepath.empty()) {
            continue;
        }

        types::filetime_t new_time{fs::last_write_time(current_file.filepath)};
        if (current_file.last_modified < new_time) {
            current_file.last_modified = new_time;

            //printf("Last modification: %s", ctime(&file_stat.st_mtime)); //TODO: if verbose
            return true;
        }
    }

    return false;
}
