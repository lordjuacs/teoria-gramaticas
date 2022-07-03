#include "test.h"

int main() {
    int rules_size = 1000;
    int variable_size = 25;
    int terminal_size = 25;
    int minimo_regla = 950;
    int maximo_regla = 1000;
    if (rules_size > 1000000)
        return 0;

    /*std::cout << "terminal_size: " << terminal_size << std::endl;
    std::cout << "variable_size: " << variable_size << std::endl;
    std::cout << "rules_size: " << rules_size << std::endl;
    std::cout << "-------------------------------" << std::endl;
    */
    //  clock_t start = clock();
    Test test;
    auto test_ans = test.run_test("output.txt", terminal_size, variable_size, rules_size, maximo_regla, minimo_regla);
    // clock_t end = clock();
    //  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    //   std::cout << "Time spent TEST: " << time_spent << std::endl;
    //   std::cout << "-------------------------------" << std::endl;

    // start = clock();
    // std::cout << "llegue";

    GIC gic("output.txt");
    // gic.print();
    auto algo_ans = gic.test_vacio_quadratic();
    // end = clock();
    // time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    //  std::cout << "Time spent SOLUTION: " << time_spent << std::endl;

    // std::cout << "-------------------------------" << std::endl;

    if (test_ans != algo_ans) {
        std::cout << "error\n";

    } else {
        std::cout << "bien";
    }

    return 0;
}