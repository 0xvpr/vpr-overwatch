/**
 * Created by:      VPR
 * Created:         January 17th, 2023
 *
 * Updated by:      VPR
 * Updated:         April 14th, 2024
 *
 * Description:     A file/directory watching utility that executes a specified
 *                  command if the modification time of a file(s) changes.
**/

#include "watcher.hpp"
#include "parser.hpp"
#include "types.hpp"
#include "util.hpp"

#include <iostream>
#include <chrono>
#include <thread>

using std::chrono::time_point_cast;
using std::chrono::steady_clock;

constexpr auto init_stdio = []() {
    return (std::uint64_t)std::ios::sync_with_stdio(false) |
           (std::uint64_t)std::cout.tie(nullptr);
};

int main(int argc, char** argv) {
    init_stdio();

    types::err_t err{};
    parser p = parser(argc, argv, err);
    if (err.code) {
        util::usage(argv[0], err);
    }

    const auto& args = p.parsed_args();
    (args.no_initial_exec == true) && system(args.command.c_str());

    types::files_t files = util::get_files(args);

    while (true) {
        auto start_time_us = ::time_point_cast<types::microseconds_t>(::steady_clock::now());

        watch_files(files, args);

        auto elapsed_time_us = ::time_point_cast<types::microseconds_t>(::steady_clock::now()) - start_time_us;
        auto remaining_time_us = args.frequency_us - elapsed_time_us;

        std::this_thread::sleep_for(
            args.frequency_us != types::microseconds_t{0}
            ? args.frequency_us - remaining_time_us
            : types::microseconds_t{static_cast<int>(1E5)} - remaining_time_us
        );
    }

    return 0;
}
