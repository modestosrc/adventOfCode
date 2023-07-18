#include <fstream>
#include <iostream>
#include <string>
#include <array>

struct Max {
    private:
        std::array<int, 3> arr;

    public:
        Max() : arr {0, 0, 0} {}

        void setMax(int novoMax) {
            for (int i = 0; i < arr.size(); i++) {
                if (novoMax <= arr[i]) continue;
                for (int j = arr.size() - 1; j > i; j--)
                    arr[j] = arr[j-1];
                arr[i] = novoMax;
                break;
            }
        }

        //void setMax(int novoMax) {
        //    if (novoMax > arr[0]) {
        //        arr[2] = arr[1];
        //        arr[1] = arr[0];
        //        arr[0] = novoMax;
        //    }
        //    else if (novoMax > arr[1]) {
        //        arr[2] = arr[1];
        //        arr[1] = novoMax;
        //    }
        //    else if (novoMax > arr[2])
        //        arr[2] = novoMax;
        //    else
        //        return;
        //}

        void printRespostas() {
            std::cout << "Resposta 1: " << arr[0] << std::endl;
            std::cout << "Resposta 2: " << (arr[0] + arr[1] + arr[2]) << std::endl;
        }
};

int main() {
    std::ifstream arquivo("input");
    if (!arquivo.is_open()) {
        std::cerr << "Erro abrindo arquivo" << std::endl;
        return 1;
    }

    std::string linha;
    int acumulador{0};
    Max max;

    while (getline(arquivo, linha)) {
        if (linha == "") {
            max.setMax(acumulador);
            acumulador = {0};
            continue;
        }
        
        acumulador += stoi(linha);
    }

    max.printRespostas();

    arquivo.close();
}
