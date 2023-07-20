#include <cctype>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Dir {
    std::string nome;
    int tamanhoTotal;
    int tamanhoArquivos;
    std::string dirAnterior;

    Dir(std::string nn) :
        nome(nn), 
        tamanhoTotal(0),
        tamanhoArquivos(0),
        dirAnterior("Nada")
    {
    };

    Dir(std::string nn, std::string da) :
        nome(nn),
        tamanhoTotal(0),
        tamanhoArquivos(0),
        dirAnterior(da)
        {
        };

};

std::vector<Dir> dirs;

std::string dirAnterior(std::string atual) {
    std::string novoDir;
    for (Dir dir : dirs) {
        if (dir.nome == atual) {
            novoDir = dir.dirAnterior;
            return novoDir;
        }
    }
    return novoDir;
}

void addValor(std::string dirA, int valor) {
    std::cout << "Adicionado a: " << dirA << std::endl;
    if (dirA == "/") {
        for (Dir &dir : dirs) {
            if (dir.nome == "/") {
                dir.tamanhoArquivos += valor;
                break;
            }
        }
    } else {
        for (Dir &dir : dirs) {
            if (dir.nome == dirA) {
                dir.tamanhoArquivos += valor;
                addValor(dirAnterior(dirA), valor);
            }
        }
    }
    return;
}

void check(std::string dirA) {
    for (Dir dir : dirs) {
        if (dir.nome == dirA) {
            std::cout << dir.nome            << " "
                      //<< dir.tamanhoTotal    << " "
                      << dir.tamanhoArquivos << " "
                      << dir.dirAnterior     << " "
                      << std::endl;
        }
    }
}

int main() {
    std::ifstream arquivo("input");
    std::string dirAtual;
    std::string s;

    while (std::getline(arquivo, s)) {
        if (s.at(0) == '$') {
            switch (s.at(2)) {
                case 'c':
                    s.erase(0, 5);
                    if (s[0] == '/') {
                        dirs.push_back(Dir("/"));
                        dirAtual = dirs.back().nome;
                        break;
                    };
                    if (s[0] == '.') {
                        dirAtual = dirAnterior(dirAtual);
                    } else {
                        dirs.push_back(Dir(s, dirAtual));
                        dirAtual = dirs.back().nome;
                    }
                    break;
                case 'l':
                    continue;
                default:
                    break;
            }
        } else if (std::isdigit(s.at(0))) {
            addValor(dirAtual, std::stoi(s.substr(0, s.find(' '))));
            }
    }

    for (auto item : dirs) {
        std::cout << "Nome: " << item.nome 
                  << " Tamanho arquivos: " << item.tamanhoArquivos 
                  //<< " Tamanho total: "  << item.tamanhoTotal << " "
                  << " Dir Anterior: " << item.dirAnterior << std::endl;
    }

    arquivo.close();
}
