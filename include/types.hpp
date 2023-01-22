#ifndef TYPES_HEADER
#define TYPES_HEADER

#include <filesystem>

namespace types {
    using filetime_t    = std::filesystem::file_time_type;
    using cstring_t     = const char * const __restrict;
    using nanoseconds_t = std::chrono::nanoseconds;

    namespace errcodes {
        constexpr int missing_arguments       = -1;
        constexpr int invalid_arguments       = 1;
        constexpr int unsupported_arguments   = 2;
    }

    typedef struct ParsedArgs {
        bool                    no_initial_exec;
        bool                    recursive;
        int32_t                 verbosity;
        types::nanoseconds_t    frequency_us;
        char                    command[256];
        char                    filepath[256];
        char                    program_name[256];
    } parsedargs_t;

    typedef struct FileInfo {
        FileInfo(filetime_t last_write_time, cstring_t file_path_in)
            : last_modified(last_write_time)
        {
            for (size_t i = 0; (*(relative_file_path+i) = *(file_path_in+i)) && i < sizeof(relative_file_path); ++i);
        }

        filetime_t  last_modified;
        char        relative_file_path[256];
    } fileinfo_t;
} // types

#endif // TYPES_HEADER
