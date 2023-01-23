#include "test.hpp"

#include "watcher_test.hpp"
#include "parser_test.hpp"
#include "util_test.hpp"

#include <iostream>

int main() {
    TestSuite test_suite{};

    test_suite.Execute("parser_test::correct_positional_arguments", parser_test::correct_positional_arguments);

    return 0;
}
