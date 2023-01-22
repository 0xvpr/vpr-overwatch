#include "tests.hpp"
#include "watcher_test.hpp"
#include "parser_test.hpp"
#include "util_test.hpp"

#include <iostream>

int main() {
    TestSuite test_suite{};

    test_suite.Execute([]() -> void { std::cout << "Test Suite\n"; });

    // Display passes
    // Display fails

    return 0;
}
