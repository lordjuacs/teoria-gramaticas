#include "gic.h"

class Test {
   private:
    std::vector<std::string> terminals;  // minusculas
    std::vector<std::string> variables;  // mayusculas
    std::list<Regla> rules;
    std::vector<std::string> generadores;
    std::string inicial;
    int total_rules;

   public:
    Test(const std::string& output, int terminal_size, int variable_size, int rules_size) {
        // if terminal_size is 0 or greater than 26, return, the same with variable_size
        if (terminal_size < 0 || terminal_size > 26)
            return;
        if (variable_size < 0 || variable_size > 26)
            return;
        if (rules_size < 0)
            return;
        if (rules_size < variable_size)
            return;

        srand(time(NULL));
        for (int i = 0; i < terminal_size; i++) {
            std::string s = "";
            s += (char)('a' + rand() % 26);
            // only push back s if s is not already in terminals, otherwise find another s
            if (std::find(terminals.begin(), terminals.end(), s) == terminals.end()) {
                terminals.push_back(s);
            } else {
                i--;
            }
        }
        // generate a vector of unique random uppercase letters, the size of such vector is variable_size
        for (int i = 0; i < variable_size; i++) {
            std::string s = "";
            s += (char)('A' + rand() % 26);
            // only push back s if s is not already in variables, otherwise find another s
            if (std::find(variables.begin(), variables.end(), s) == variables.end()) {
                variables.push_back(s);
            } else {
                i--;
            }
        }
        // inicial is a random uppercase letter from variables
        inicial = variables[rand() % variables.size()];

        std::vector<std::string> not_yet_v = variables;

        // generate a list of rules, the size of such list is rules_size
        generadores = terminals;
        total_rules = rules_size;
        // generate a list of rules, the size of such list is 10 percent of rules_size
        // such that left is a varible, and right consists of only terminals
        int rules_size_terminal = rules_size * 0.2;
        for (int i = 0; i < rules_size_terminal; i++) {
            std::string left = variables[rand() % variables.size()];
            std::string right = "";
            // right has a random number of terminals, between 1 and terminal_size
            int right_size = rand() % terminal_size + 1;
            for (int j = 0; j < right_size; j++) {
                right += terminals[rand() % terminals.size()];
            }
            rules.push_back(Regla{left, right});
            // take out the left from not_yet_v
            not_yet_v.erase(std::remove(not_yet_v.begin(), not_yet_v.end(), left), not_yet_v.end());
        }

        // for each left in the current rules, insert left in generadores if it is not already in generadores
        for (auto& rule : rules) {
            if (std::find(generadores.begin(), generadores.end(), rule.left) == generadores.end()) {
                generadores.push_back(rule.left);
            }
        }
        // generate a list of rules such that right consistes of a mix of terminals and variables, the right size is between 1 and terminal_size + variable_size
        // rules_size_mix is the sixth of rules_size

        std::list<Regla> mix;
        int rules_size_mix = rules_size * 0.8;
        for (int i = 0; i < rules_size_mix; i++) {
            std::string left;
            if (!not_yet_v.empty()) {
                left = not_yet_v[rand() % not_yet_v.size()];
                not_yet_v.erase(std::remove(not_yet_v.begin(), not_yet_v.end(), left), not_yet_v.end());
            } else {
                left = variables[rand() % variables.size()];
            }

            std::string right = "";
            // right has a random number of terminals and variables, between 1 and terminal_size + variable_size
            int right_size = rand() % (terminal_size + variable_size) + 1;
            for (int j = 0; j < right_size; j++) {
                // right consists of random terminals and variables
                if (rand() % 2 == 0) {
                    right += terminals[rand() % terminals.size()];
                } else {
                    right += variables[rand() % variables.size()];
                }
            }
            mix.push_back(Regla{left, right});
        }
        // for each left in mix, if all elements in right are in generadores, insert left in generadores if it is not already in generadores
        for (auto& rule : mix) {
            bool all_in_generadores = true;
            for (auto& c : rule.right) {
                if (std::find(generadores.begin(), generadores.end(), std::string(1, c)) == generadores.end()) {
                    all_in_generadores = false;
                    break;
                }
            }
            if (all_in_generadores) {
                if (std::find(generadores.begin(), generadores.end(), rule.left) == generadores.end()) {
                    generadores.push_back(rule.left);
                }
            }
        }

        // add mix to rules
        rules.insert(rules.end(), mix.begin(), mix.end());
        std::sort(terminals.begin(), terminals.end());
        std::sort(variables.begin(), variables.end());
        std::sort(generadores.begin(), generadores.end());

        // print();

        // if inicial in generadores, print TEST VACIO: SI, else print TEST VACIO: NO
        std::cout << "TEST VACIO: ";
        check_test_vacio() ? std::cout << "SI" << std::endl : std::cout << "NO" << std::endl;

        // write the contents of terminals, variables, rules to a file
        std::ofstream file(output);
        for (auto& t : terminals) {
            file << t;
        }
        file << std::endl;
        for (auto& v : variables) {
            file << v;
        }
        file << std::endl;
        file << rules_size << std::endl;
        // write rules to file, such that the first written has left equal to inicial
        for (auto& rule : rules) {
            if (rule.left == inicial) {
                file << inicial << " " << rule.right << std::endl;
            }
        }
        for (auto& rule : rules) {
            if (rule.left != inicial) {
                file << rule.left << " " << rule.right << std::endl;
            }
        }
    }
    void print() {
        std::cout << "Terminales: ";
        for (auto& t : terminals) {
            std::cout << t << " ";
        }
        std::cout << std::endl;
        std::cout << "Variables: ";
        for (auto& v : variables) {
            std::cout << v << " ";
        }
        // print inicial
        std::cout << std::endl
                  << "Inicial: " << inicial << std::endl;
        std::cout << "Total producciones: " << total_rules << std::endl;
        std::cout << "Producciones: " << std::endl;
        for (auto& p : rules) {
            std::cout << p.left << " -> " << p.right << std::endl;
        }
        std::cout << "Generadores: ";
        for (auto& g : generadores) {
            std::cout << g << " ";
        }
        std::cout << std::endl;
    }
    bool check_test_vacio() {
        if (std::find(generadores.begin(), generadores.end(), inicial) == generadores.end()) {
            return true;
        }
        return false;
    }
    ~Test() {
    }
    void test_gic() {
    }
};
