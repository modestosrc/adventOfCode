#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

enum Jogadas{
    PEDRA   = 0,
    PAPEL   = 1,
    TESOURA = 2
};

enum Resultado{
    DERROTA  = 0,
    EMPATE   = 3,
    VITORIA  = 6
};

int fazJogada1(std::string s) {
    auto m{s[0] == 'A' ? PEDRA : (
           s[0] == 'B' ? PAPEL : TESOURA)};
    auto n{s[2] == 'X' ? PEDRA : (
           s[2] == 'Y' ? PAPEL : TESOURA)};

    static int tabelaRes[3][3]{
        {EMPATE,  VITORIA,  DERROTA },
        {DERROTA, EMPATE,  VITORIA  },
        {VITORIA, DERROTA, EMPATE   }
    };

    return (tabelaRes[m][n] + (n + 1));
}

int fazJogada2(std::string s) {
    auto m{s[0] == 'A' ? PEDRA : (
           s[0] == 'B' ? PAPEL : TESOURA)};
    auto n{s[2] == 'X' ? DERROTA: (
           s[2] == 'Y' ? EMPATE: VITORIA)};

    static int tabelaRes[3][3]{
        {TESOURA,  PEDRA,   PAPEL},
        {PEDRA,    PAPEL,   TESOURA},
        {PAPEL,    TESOURA, PEDRA}
    };

    return ((tabelaRes[m][n/3] + 1) + n);
}

int main() {
    std::ifstream arquivo("input");
    std::string linha;
    int acumulador{0}, acumulador2{0};

    while (getline(arquivo, linha)) {
        acumulador  += fazJogada1(linha);
        acumulador2 += fazJogada2(linha);
    }

    std::cout << "Resultado 1: " << acumulador  << std::endl;
    std::cout << "Resultado 2: " << acumulador2 << std::endl;
}
