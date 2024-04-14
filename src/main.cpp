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
#include <thread>

int main(int argc, char** argv) {
    types::err_t err{};
    parser p = parser(argc, argv, err);

    if (err.code) {
        util::usage(argv[0], err); // [[ noreturn ]]
    }

    const auto& args = p.parsed_args();
    args.initial_exec && system(args.command.c_str());

    auto files = util::get_files(args);
    while (true) {
        watch_files(files, args);

        std::this_thread::sleep_for( args.frequency_us ); // default 2 ms
    }

    return 0;
}
