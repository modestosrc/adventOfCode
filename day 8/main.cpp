#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int contaArvoresVisiveis(std::vector<std::vector<int>> arvores);
int medeScoreCenico(std::vector<std::vector<int>> arvores);

int main() {
    std::ifstream arquivo("input");

    std::vector<std::vector<int>> arvores;
    std::string s;
    int cont{0};
    while(std::getline(arquivo, s)) {
        arvores.push_back(std::vector<int>());
        for (char c : s)
            arvores[cont].push_back(c - '0');
        cont++;
    }

    //for (std::vector vec : arvores) {
    //    for (int a : vec)
    //        std::cout << a;
    //    std::cout << std::endl;
    //}

    int arvores_visiveis{contaArvoresVisiveis(arvores)};
    int maior_score{medeScoreCenico(arvores)};

    std::cout << "Resultado 1: " << arvores_visiveis << std::endl;
    std::cout << "Resultado 2: " << maior_score << std::endl;

    arquivo.close();
}

int contaArvoresVisiveis(std::vector<std::vector<int>> arvores) {
    int arvores_visiveis{0};
    for (int i{0}; i < arvores.size(); i++) {
        for (int j{0}; j < arvores[i].size(); j++) {
            if (i == 0 || i == arvores.size() - 1)
            {arvores_visiveis++; continue;}

            if (j == 0 || j == arvores[i].size() - 1)
            {arvores_visiveis++; continue;}

            int linha = i; 
            int coluna = j;
            while (linha > 0) {
                if (arvores[i][j] <= arvores[linha - 1][coluna]) break;
                if (linha == 1) {
                    arvores_visiveis++; 
                    goto END;
                }
                linha--; 
            }
            linha = i; 
            while (coluna > 0) {
                if (arvores[i][j] <= arvores[linha][coluna - 1]) break;
                if (coluna == 1) {
                    arvores_visiveis++;
                    goto END;
                }
                coluna--; 
            }
            coluna = j;            
            while (linha < arvores.size() - 1) {
                if (arvores[i][j] <= arvores[linha + 1][coluna]) break;
                if (linha == arvores.size() - 2) {
                    arvores_visiveis++;
                    goto END;
                }
                linha++; 
            }
            linha = i; 
            while (coluna < arvores[i].size() - 1) {
                if (arvores[i][j] <= arvores[linha][coluna + 1]) break;
                if (coluna == arvores[i].size() - 2) {
                    arvores_visiveis++;
                    goto END;
                }
                coluna++; 
            }
            END:
            continue;
        }
    }
    return arvores_visiveis;
}

int medeScoreCenico(std::vector<std::vector<int>> arvores) {
    int score{0};

    for (int i{0}; i < arvores.size(); i++) {
        for (int j{0}; j < arvores[i].size(); j++) {
            if (i == 0) continue;
            if (i == arvores.size() - 1) continue;
            if (j == 0) continue;
            if (j == arvores[i].size() - 1) continue;

            int cima{1}, baixo{1}, esquerda{1}, direita{1};
            int linha{i};
            int coluna{j};
            while (arvores[i][j] > arvores[linha - 1][coluna]) {
                if (linha <= 1) break;
                cima++;
                linha--;
            }
            linha = i;
            while (arvores[i][j] > arvores[linha][coluna - 1]) {
                if (coluna <= 1) break;
                esquerda++;
                coluna--;
            }
            coluna = j;
            while (arvores[i][j] > arvores[linha + 1][coluna]) {
                if (linha >= arvores.size() - 2) break;
                baixo++;
                linha++;
            }
            linha = i;
            while (arvores[i][j] > arvores[linha][coluna + 1]) {
                if (coluna >= arvores[i].size() - 2) break;
                direita++;
                coluna++;
            }
            int novo_score{cima * baixo * esquerda * direita};
            score = score < novo_score ? novo_score : score;
        }
    }
    return score;
}
