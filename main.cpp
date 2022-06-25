#include "test.h"

int main() {
    int terminal_size = 26;
    int variable_size = 26;
    int rules_size = 100;
    Test test("output.txt", terminal_size, variable_size, rules_size);
    std::cout << "-------------------------------" << std::endl;
    GIC gic;
    // gic.print();
    gic.test_vacio_quadratic();

    return 0;
}