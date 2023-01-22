/**
 * Created by:      VPR
 * Created:         January 17th, 2023
 *
 * Updated by:      VPR
 * Updated:         January 22nd, 2023
 *
 * Description:     A file/directory watching utility that executes a specified
 *                  command if the modification time of a file(s) changes.
**/

#include "watcher.hpp"
#include "parser.hpp"
#include "types.hpp"
#include "util.hpp"

#include <chrono>
#include <thread>

using std::chrono::time_point_cast;
using std::chrono::steady_clock;

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(true);

    auto parsedArgs = parse_args(argc, argv);
    auto files = util::get_files(parsedArgs);

    int32_t command_rv;
    if (!parsedArgs.no_initial_exec && (command_rv = system(parsedArgs.command))) {
        return command_rv;
    }

    while (true) {
        auto start_time_us = ::time_point_cast<types::nanoseconds_t>(::steady_clock::now());

        watch_files(files, parsedArgs);

        auto elapsed_time_us = ::time_point_cast<types::nanoseconds_t>(::steady_clock::now()) - start_time_us;
        auto remaining_time_us = parsedArgs.frequency_us - elapsed_time_us;

        std::this_thread::sleep_for(parsedArgs.frequency_us != types::nanoseconds_t{0}
            ? parsedArgs.frequency_us - remaining_time_us
            : types::nanoseconds_t{static_cast<int>(1E5)} - remaining_time_us);
    }

    return 0;
}
