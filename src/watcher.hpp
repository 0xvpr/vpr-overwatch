#ifndef WATCHER_HEADER
#define WATCHER_HEADER

#include "types.hpp"

#include <vector>

/**
 * TODO
**/
void watch_files(std::vector<types::file_info_t>& files, const types::parsed_args_t& parsed_args);

#endif // WATCHER_HEADER
