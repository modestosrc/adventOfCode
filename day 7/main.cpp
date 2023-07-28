#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Dir {
    int tamanhoArquivos;
    const std::string nome;
    const std::string dirAnterior;

    Dir(std::string nn, std::string da) :
        nome(nn),
        tamanhoArquivos(0),
        dirAnterior(da)
        {
        };

};

std::vector<Dir> dirs;

std::string findDirAnterior(const std::string atual) {
    for (Dir dir : dirs) {
        if (dir.nome == atual) {
            return dir.dirAnterior;
        }
    }
    return "Isso não deveria acontecer";
}

void addValor(const std::string dirA, const int valor) {
    //std::cout << "Adicionado a: " << dirA << std::endl;
    if (dirA == "/") {
        for (Dir &dir : dirs) {
            if (dir.nome == "/") {
                dir.tamanhoArquivos += valor;
                return;
            }
        }
    } else {
        for (Dir &dir : dirs) {
            if (!dir.nome.compare(dirA)) {
                dir.tamanhoArquivos += valor;
                addValor(findDirAnterior(dirA), valor);
                return;
            }
        }
    }
}

bool check(std::string dirA) {
    for (Dir dir : dirs) {
        if (dir.nome == dirA) {
            return false;
        }
    }
    return true;
}

int main() {
    dirs.reserve(200);
    std::ifstream arquivo("input");
    std::string dirAtual{"root"};
    std::string s;

    int cont{0};

    while (std::getline(arquivo, s)) {
        if (s.at(0) == '$') {
            switch (s.at(2)) {
                case 'c':
                    s.erase(0, 5);
                    //if (s[0] == '/') {
                    //    dirs.push_back(Dir("/"));
                    //    dirAtual = dirs.back().nome;
                    //    continue;;
                    //};
                    if (s[0] == '.' && s[1] == '.') {
                        cont++;
                        dirAtual = findDirAnterior(dirAtual);
                        continue;
                    } 
                    if (check(s)) {
                        dirs.push_back(Dir(s, dirAtual));
                        dirAtual = dirs.back().nome;
                        continue;
                    }
                    continue;
                case 'l':
                    continue;
            }
        } else if (s.at(0) == 'd') {
            continue;
        } else if (std::isdigit(s.at(0))) {
            addValor(dirAtual, std::stoi(s.substr(0, s.find(' '))));
            continue;
        }
    }

    int resposta{0};
    for (Dir item : dirs) {
        if (item.tamanhoArquivos <= 100000) {
            resposta += item.tamanhoArquivos;
        }
        std::cout << "Nome: " << item.nome 
                  << " \tTamanho arquivos: " << item.tamanhoArquivos
                  << " \tDir Anterior: " << item.dirAnterior 
                  << std::endl;
    }

    std::cout << cont << " Resposta: " << resposta << std::endl;

    arquivo.close();
}
