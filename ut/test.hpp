#ifndef TEST_HEADER
#define TEST_HEADER

#include <iostream>

class TestSuite {
public:
    TestSuite()
        : passes(0)
        , fails(0)
        , skipped(0)
    {
        std::cout << "TestSuite Initiated...\n"
                  << "\n";
    }
    ~TestSuite()
    {
        std::cout << "\n"
                  << "  Tests executed:\t" << passes + fails + skipped << "\n"
                  << "\n"
                  << "  Passes:\t\t"       << passes  << "\n"
                  << "  Fails:\t\t"        << fails   << "\n"
                  << "  Skipped:\t\t"      << skipped << "\n";
    }
public:
    template <typename ...Ts>
    void Execute(const char * __restrict test_name, auto&& function, Ts... args) {
        auto rv = function(args...);
        std::cout << "  Test: '" << test_name << [=]() {
            if (rv == 0) {
                return "' passed.";
            } else if (rv == 1) {
                return "' failed.";
            }
            return "' skipped.";
        }() << "\n";

        passes  += rv == 0; 
        fails   += rv == 1;
        skipped += rv == -1;
    }
private:
    int passes;
    int fails;
    int skipped;
};

#endif //TESTS_HEADER
