#include "parser_test.hpp"

#include "test_types.hpp"
#include "parser.hpp"

#include <string>

int parser_test::correct_positional_arguments() {
    int argc = 3;
    const char * argv[3] = { "vpr-overwatch", "." , "echo testing" };
    auto parsedArgs = parse_args(argc, (char **) argv);

    if (parsedArgs.no_initial_exec == true) {
        return test_types::return_codes::failed;
    }

    if (parsedArgs.recursive == true) {
        return test_types::return_codes::failed;
    }

    if (parsedArgs.frequency_us != types::nanoseconds_t{0}) {
        return test_types::return_codes::failed;
    }

    if (parsedArgs.verbosity != 0) {
        return test_types::return_codes::failed;
    }

    if (std::string_view(parsedArgs.command) != std::string_view(argv[2])) {
        return test_types::return_codes::failed;
    }

    if (std::string_view(parsedArgs.filepath) != std::string_view(argv[1])) {
        return test_types::return_codes::failed;
    }

    return 0;
}

// TODO: refactor for this
//int parser_test::incorrect_positional_arguments_missing_args() {
    //int argc = 3;
    //const char * argv[3] = { "vpr-overwatch", "." , "echo testing" };
    //auto parsedArgs = parse_args(argc, (char **) argv);

    //if (parsedArgs.no_initial_exec == true) {
        //return test_types::return_codes::failed;
    //}

    //if (parsedArgs.recursive == true) {
        //return test_types::return_codes::failed;
    //}

    //if (parsedArgs.frequency_us != types::nanoseconds_t{0}) {
        //return test_types::return_codes::failed;
    //}

    //if (parsedArgs.verbosity != 0) {
        //return test_types::return_codes::failed;
    //}

    //if (std::string_view(parsedArgs.command) != std::string_view(argv[2])) {
        //return test_types::return_codes::failed;
    //}

    //if (std::string_view(parsedArgs.filepath) != std::string_view(argv[1])) {
        //return test_types::return_codes::failed;
    //}

    //return 0;
//}
