#include "parser_test.hpp"

#include "test_types.hpp"
#include "parser.hpp"

int parser_test::correct_positional_arguments() {
    int argc = 3;
    const char * argv[3] = { "vpr-overwatch", "." , "echo testing" };

    types::err_t err;
    auto parsed_args = parser(argc, (char **) argv, err).parsed_args();

    if (err.code) {
        return test_types::return_codes::failed;
    }

    if (parsed_args.no_initial_exec == true) {
        return test_types::return_codes::failed;
    }

    if (parsed_args.recursive == true) {
        return test_types::return_codes::failed;
    }

    if (parsed_args.frequency_us != types::microseconds_t{0}) {
        return test_types::return_codes::failed;
    }

    if (parsed_args.verbosity != 0) {
        return test_types::return_codes::failed;
    }

    if (std::string_view(parsed_args.command) != std::string_view(argv[2])) {
        return test_types::return_codes::failed;
    }

    if (std::string_view(parsed_args.filepaths[0]) != std::string_view(argv[1])) {
        return test_types::return_codes::failed;
    }

    return 0;
}

// TODO: refactor for this
//int parser_test::incorrect_positional_arguments_missing_args() {
    //int argc = 3;
    //const char * argv[3] = { "vpr-overwatch", "." , "echo testing" };
    //auto parsed_args = parse_args(argc, (char **) argv);

    //if (parsed_args.no_initial_exec == true) {
        //return test_types::return_codes::failed;
    //}

    //if (parsed_args.recursive == true) {
        //return test_types::return_codes::failed;
    //}

    //if (parsed_args.frequency_us != types::microseconds_t{0}) {
        //return test_types::return_codes::failed;
    //}

    //if (parsed_args.verbosity != 0) {
        //return test_types::return_codes::failed;
    //}

    //if (std::string_view(parsed_args.command) != std::string_view(argv[2])) {
        //return test_types::return_codes::failed;
    //}

    //if (std::string_view(parsed_args.filepath) != std::string_view(argv[1])) {
        //return test_types::return_codes::failed;
    //}

    //return 0;
//}
