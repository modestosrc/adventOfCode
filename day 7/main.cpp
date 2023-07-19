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
    Dir *dirAnterior;

    Dir(std::string nn) :
        nome(nn), 
        tamanhoTotal(0),
        tamanhoArquivos(0),
        dirAnterior(nullptr)
    {
        std::cout << "Criado: " << nome << std::endl;
    };

    Dir(std::string nn, Dir *da) :
        nome(nn),
        tamanhoTotal(0),
        tamanhoArquivos(0),
        dirAnterior(da)
        {
            std::cout << "Criado: " << nome;
            std::cout << " | Pai: " << da->nome;
            std::cout << std::endl;
        };
};

int main() {
    std::ifstream arquivo("input");
    std::vector<Dir> dirs;
    Dir *pDir{nullptr};
    dirs.emplace_back(Dir("/"));
    pDir = &dirs.back();
    dirs.emplace_back(Dir("mateus", pDir));
    pDir = &dirs.back();
    std::cout << pDir << pDir->nome << pDir->dirAnterior << std::endl;
    pDir = pDir->dirAnterior;
    std::cout << pDir << pDir->nome << std::endl;

    std::string s;
    while (std::getline(arquivo, s)) {
        if (s.at(0) == '$') {
            switch (s.at(2)) {
                case 'c':
                    s.erase(0, 5);
                    if (s[0] == '/') break;
                    if (s[0] == '.') {
                        //std::cout << pDir->dirAnterior->nome;
                        pDir = pDir->dirAnterior;
                    } else {
                        for (Dir item : dirs) {
                            if (item.nome == s) {
                                pDir = &item;
                                break;
                            }
                        }
                        dirs.emplace_back(Dir(s, pDir));
                        pDir = &dirs.back();
                    }
                    break;
                case 'l':
                    continue;
                    break;
                default:
                    break;
            }
        } else if (std::isdigit(s.at(0))) {
            std::string token = s.substr(0, s.find(' '));
            int tamanho = std::stoi(token);
            pDir->tamanhoArquivos += tamanho;
            pDir->tamanhoTotal += tamanho;
            //std::cout << pDir->nome << std::endl;
            Dir *pDir_tmp = pDir;
            while (pDir->nome != "/") {
                //std::cout << pDir->nome << std::endl;
                pDir->dirAnterior->tamanhoTotal += tamanho;
                std::cout << "Functionou! " << pDir->dirAnterior->nome << " " << pDir->dirAnterior->tamanhoTotal << std::endl;
                pDir = pDir->dirAnterior;
                std::cout << "Functionou! " << pDir->nome << " " << pDir->tamanhoTotal << std::endl;
            }
            pDir = pDir_tmp;
        } else continue;
    }

    for (auto item : dirs) {
        //if (item.nome == "/") continue;
        std::cout << item.nome << " Tamanho arquivos: " 
                  << item.tamanhoArquivos << " Tamanho total: " 
                  << item.tamanhoTotal << " "
                  << item.dirAnterior->nome << std::endl;
    }
}
