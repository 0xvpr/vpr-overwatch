#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <filesystem>
#include <vector>

#include "parser.hpp"
#include "types.hpp"

namespace util {

    /**
     * TODO
    **/
    [[noreturn]] void usage(const char * const __restrict program, const char* const __restrict msg, types::errcodes code);

    /**
     * TODO
    **/
    [[noreturn]] void usage(const char * const __restrict program, const types::err_t& err);

    /**
     * TODO
    **/
    [[nodiscard]] types::files_t get_files(const types::parsed_args_t& parsed_args);
}

#endif // UTIL_HEADER
