#include <array>
#include <fstream>
#include <iostream>
#include <string>


int decideValor(std::string s) {
    std::array<int, 52> bitMap{0};

    for (int i{0}; i < s.size(); i++) {
        char c{s[i]};
        int posi{( c >= 'a' ? (c - 'a') : (c - 'A' + 26) )};
        if (i < (s.size() / 2)) {
            bitMap[posi] |= 1 << 0;
        } else {
            if (bitMap[posi] == 1)
                return posi + 1;
        }
    }

    return 0;
}

int decideValor2(std::string s) {
    static int linha{0}; linha++;
    static std::array<int, 52> bitMap{0};
    int resposta{0};

    for (int i{0}; i < s.size(); i++) {
        char c{s[i]};
        int idLinha = linha % 3;
        int posi{( c >= 'a' ? (c - 'a') : (c - 'A' + 26) )};

        bitMap[posi] |= 1 << idLinha;

        if (bitMap[posi] == 7) {
            bitMap.fill(0);
            return posi + 1;
        }
    }

    return 0;
}


int main() {
    std::ifstream arquivo("input");
    std::string s;
    int acumulador{0}, acumulador2{0};
    
    while (std::getline(arquivo, s)) {
        acumulador  += decideValor(s);
        acumulador2 += decideValor2(s);
    }

    std::cout << "Resposta 1: " << acumulador  << std::endl;
    std::cout << "Resposta 2: " << acumulador2 << std::endl;
    arquivo.close();
}
