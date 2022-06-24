#include "gic.h"

class Test {
   public:
    Test(const std::string& output, int terminal_size, int variable_size, int rules_size) {
        // if terminal_size is 0 or greater than 26, return, the same with variable_size
        if (terminal_size < 0 || terminal_size > 26)
            return;
        if (variable_size < 0 || variable_size > 26)
            return;
        if (rules_size < 0)
            return;

        srand(time(NULL));
        std::vector<std::string> terminals;
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
        std::vector<std::string> variables;
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
        std::string inicial = variables[rand() % variables.size()];

        // generate a list of rules, the size of such list is rules_size
        std::list<Regla> rules;
        std::vector<std::string> generadores = terminals;

        // generate a list of rules, the size of such list is 10 percent of rules_size
        // such that left is a varible, and right consists of only terminals
        int rules_size_terminal = rules_size * 0.1;
        for (int i = 0; i < rules_size_terminal; i++) {
            std::string left = variables[rand() % variables.size()];
            std::string right = "";
            // right has a random number of terminals, between 1 and terminal_size
            int right_size = rand() % terminal_size + 1;
            for (int j = 0; j < right_size; j++) {
                right += terminals[rand() % terminals.size()];
            }
            rules.push_back(Regla{left, right});
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
        int rules_size_mix = rules_size * 0.6;
        for (int i = 0; i < rules_size_mix; i++) {
            std::string left = variables[rand() % variables.size()];
            std::string right = "";
            // right has a random number of terminals and variables, between 1 and terminal_size + variable_size
            int right_size = rand() % (terminal_size + variable_size) + 1;
            for (int j = 0; j < right_size; j++) {
                right += generadores[rand() % terminals.size()];
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


        // generate a list of rules, the size of such list is 30 percent of rules_size
        // such that left is a varible, and right consists of terminals and variables
        int rules_size_tv = rules_size * 0.3;
        for (int i = 0; i < rules_size_tv; i++) {
            std::string left = variables[rand() % variables.size()];
            std::string right = "";
            // right has a random number of terminals and variables, between 1 and terminal_size + variable_size
            int right_size = rand() % (terminal_size + variable_size) + 1;
            for (int j = 0; j < right_size; j++) {
                //right consists of random terminals and variables
                if (rand() % 2 == 0) {
                    right += terminals[rand() % terminals.size()];
                } else {
                    right += variables[rand() % variables.size()];
                }
            }
            rules.push_back(Regla{left, right});
        }

        // print all rules
        std::cout << "Rules: " << std::endl;
        for (auto& rule : rules) {
            std::cout << rule.left << " -> " << rule.right << std::endl;
        }
        // print all generadores
        std::cout << "Generadores: " << std::endl;
        for (auto& generador : generadores) {
            std::cout << generador << " ";
        }
        std::cout << std::endl;
        // print inicial
        std::cout << "Inicial: " << inicial << std::endl;
        // print terminals
        std::cout << "Terminales: " << std::endl;
        for (auto& terminal : terminals) {
            std::cout << terminal << " ";
        }
        std::cout << std::endl;
        // print variables
        std::cout << "Variables: " << std::endl;
        for (auto& variable : variables) {
            std::cout << variable << " ";
        }
        std::cout << std::endl;
        //if inicial in generadores, print TEST VACIO: SI, else print TEST VACIO: NO
        if (std::find(generadores.begin(), generadores.end(), inicial) == generadores.end()) {
            std::cout << "TEST VACIO: SI" << std::endl;
        } else {
            std::cout << "TEST VACIO: NO" << std::endl;
        }
        std::sort(terminals.begin(), terminals.end());
        std::sort(variables.begin(), variables.end());

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
    }
    ~Test() {
    }
    void test_gic() {
    }
};
