#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <filesystem>
#include <vector>

#include "parser.hpp"

namespace util {
    /**
     * TODO
    **/
    [[noreturn]] void usage(const char * const __restrict program, const char* const __restrict msg, auto code);

    /**
     * TODO
    **/
    [[nodiscard]] std::vector<types::fileinfo_t> get_files(const types::parsedargs_t& parsedArgs);
}

#endif // UTIL_HEADER
