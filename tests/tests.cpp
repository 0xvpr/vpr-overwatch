#include "tests.hpp"

#include <iostream>

int main() {
    TestSuite test_suite{};

    test_suite.Execute([]() -> void { std::cout << "Test Suite\n"; });

    // Display passes
    // Display fails

    return 0;
}
