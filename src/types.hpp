#ifndef TYPES_HEADER
#define TYPES_HEADER

#include <filesystem>
#include <vector>
#include <string>

namespace types {

typedef std::filesystem::file_time_type filetime_t;
typedef std::chrono::microseconds microseconds_t;

enum errcodes : std::int32_t {
    no_error                    = 0,
    missing_arguments           = 1,
    invalid_arguments           = 2,
    unsupported_arguments       = 3
};

constexpr std::string_view error_messages[4] = {
    "No error.",
    "Missing arguments.",
    "Invalid arguments.",
    "Unsupported option.",
};

typedef struct err {
    errcodes                    code;
    std::string                 msg;
} err, err_t;

typedef struct parsed_args {
    bool                        no_initial_exec;
    bool                        recursive;
    int32_t                     verbosity;
    microseconds_t              frequency_us;
    std::string                 command;
    std::string                 program_name;
    std::vector<std::string>    filepaths;
} parsed_args, parsed_args_t;

typedef struct file_info {
    explicit file_info(filetime_t last_write_time, const std::string& filepath_in) noexcept
      : last_modified(last_write_time)
      , filepath{filepath_in}
    {}

    filetime_t  last_modified;
    std::string filepath;
} file_info, file_info_t;

typedef std::vector<types::file_info_t> files_t;

} // namespace types

#endif // TYPES_HEADER
