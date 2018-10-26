#include <iostream>
#include <memory>

class Test {
    public:
        Test(int value) : value(value) {
            //TODO
        }
        int getValue() {
            return this->value;
        }
        void setValue(int value) {
            this->value = value;
        }
    private:
        int value;
};

int main(int argc, char** argv) {
    auto test = std::make_unique<Test>(10);
    std::cout << test->getValue() << std::endl;
    test->setValue(100);
    std::cout << test->getValue() << std::endl;
    return 0;
}