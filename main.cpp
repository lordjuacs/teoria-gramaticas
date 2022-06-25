#include "test.h"

int main() {
    Test test("output.txt", 15, 15, 20);
    std::cout << "-------------------------------" << std::endl;
    GIC gic;
    gic.print();
    gic.test_vacio_quadratic();

    // falta asegurar que cada variable este en una regla, y por ende, ahi inicial si es un random de variables
    return 0;
}