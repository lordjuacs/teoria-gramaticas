#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

struct Regla {
    std::string left;
    std::string right;
};

class GIC {
   private:
    std::vector<std::string> terminales;  // minusculas
    std::vector<std::string> variables;   // mayusculas
    std::list<Regla> producciones;
    std::vector<std::string> generadores;
    std::string inicial;
    int total_rules;

    void read_input(const std::string& filename) {
        std::string line;
        std::ifstream file(filename);
        file >> line;
        for (char c : line) {
            terminales.push_back(std::string(1, c));
        }
        file >> line;
        for (char c : line) {
            variables.push_back(std::string(1, c));
        }
        int size;
        file >> size;
        total_rules = size;
        getline(file, line);
        while (size--) {
            getline(file, line);
            std::string left = line.substr(0, line.find(' '));
            if (size == total_rules - 1)
                inicial = left;
            std::string right = line.substr(line.find(' ') + 1);
            Regla regla{left, right};
            if (right.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos) {
                producciones.push_front(regla);
            } else
                producciones.push_back(regla);
        }
        generadores = terminales;
    }

   public:
    GIC(const std::string filename) { read_input(filename); }

    void print() {
        std::cout << "Terminales: ";
        for (auto& t : terminales) {
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
        for (auto& p : producciones) {
            std::cout << p.left << " -> " << p.right << std::endl;
        }
    }

    void test_vacio_quadratic() {
        for (int i = 0; i < producciones.size(); i++) {
            std::vector<std::string> before = generadores;
            for (auto& p : producciones) {
                bool only_generadores = true;
                for (auto& c : p.right) {
                    if (std::find(generadores.begin(), generadores.end(), std::string(1, c)) == generadores.end()) {
                        only_generadores = false;
                        break;
                    }
                }
                if (only_generadores && std::find(generadores.begin(), generadores.end(), p.left) == generadores.end()) {
                    generadores.push_back(p.left);
                }
            }
            if (generadores == before) {
                std::cout << "Finalizo en " << i + 1 << " iteraciones" << std::endl;
                break;
            }
        }
        std::cout << "Generadores: ";
        for (auto& g : generadores) {
            std::cout << g << " ";
        }
        std::cout << std::endl;

        std::cout << "TEST VACIO QUADRATIC: " << std::endl;
        if (std::find(generadores.begin(), generadores.end(), inicial) == generadores.end())
            std::cout << "SI" << std::endl;
        else
            std::cout << "NO" << std::endl;
    }
};

int main() {
    GIC gic("input.txt");
    gic.print();
    gic.test_vacio_quadratic();
}