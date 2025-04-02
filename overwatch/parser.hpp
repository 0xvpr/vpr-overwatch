#ifndef PARSER_HEADER
#define PARSER_HEADER

#include "types.hpp"

class [[nodiscard]] parser {
public:
    parser() = delete;
    parser(const parser&) = delete;
    parser& operator = (const parser&) = delete;
    parser(const parser&&) = delete;
    parser& operator = (const parser&&) = delete;

    explicit parser(int argc, char** argv, types::err_t& err) noexcept;



    const types::parsed_args_t& parsed_args() const noexcept { return parsed_args_; }
private:
    types::errcodes set_flag(const std::string& flag) noexcept;
    types::errcodes parse_option(const std::string& option, const std::string& value) noexcept;



    types::parsed_args_t parsed_args_;
};

#endif // PARSER_HEADER
