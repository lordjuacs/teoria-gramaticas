#include "test.h"

int main() {
    Test test("output.txt", 15, 15, 20);
    std::cout << "-------------------------------" << std::endl;
    GIC gic;
    gic.print();
    gic.test_vacio_quadratic();

    return 0;
}