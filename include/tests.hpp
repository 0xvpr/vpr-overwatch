#ifndef TESTS_HEADER
#define TESTS_HEADER

class TestSuite {
public:
    TestSuite()
        : passes(0)
        , fails(0)
    {
    }
    int Passes() const { return passes; }
    int Fails() const { return fails; }
public:
    void Execute(auto&& function, ...);
private:
    int passes;
    int fails;
};

#endif //TESTS_HEADER
