#include <cmath>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <utility>


struct Cauda {
    static int quantidade_de_caudas;
    int x{0}, y{0}, comprimento{2}, id;
    Cauda *cauda;
    std::set<std::pair<int, int>> posi_visitadas;

    Cauda() {
        posi_visitadas.insert(std::make_pair(x, y));
        id = quantidade_de_caudas;
        quantidade_de_caudas++;
        if (quantidade_de_caudas < 9) {
            cauda = new Cauda;
        } else cauda = nullptr;
    }

    ~Cauda() {
        delete cauda;
    }

    int resposta2() {
        if (id == 8) {
            int j{0};
            for (auto i : posi_visitadas) j++;
            return j;
        } 
        return cauda->resposta2();
    }

    void move(int cx, int cy) {
        while ((std::sqrt((std::pow((cx - x), 2)) + (std::pow((cy - y) , 2)))) >= comprimento) {
            int xdif{cx - x};
            int ydif{cy - y};
            if (x != cx && y != cy) {
                if (xdif > 0) this->x += +1;
                if (ydif > 0) this->y += +1;
                if (xdif < 0) this->x += -1;
                if (ydif < 0) this->y += -1;
            }
            else if (xdif > 0) this->x += + 1;
            else if (ydif > 0) this->y += + 1;
            else if (xdif < 0) this->x += - 1;
            else if (ydif < 0) this->y += - 1;
            posi_visitadas.insert(std::make_pair(this->x, this->y));
            if (id != 8) cauda->move(this->x, this->y);
        }
    }
};

struct Cabeca {
    int x{0}, y{0};
};

struct Corda {
    Cabeca cabeca;
    Cauda *cauda;

    Corda() {
        cauda = new Cauda;
    }

    ~Corda() {
        delete cauda;
    }

    void move(std::string dir, std::string dis) {
        char direcao{dir.at(0)};
        int distancia{std::stoi(dis)};

        switch (direcao) {
            case 'U':
                cabeca.y -= distancia;
                break;

            case 'D':
                cabeca.y += distancia;
                break;

            case 'L':
                cabeca.x -= distancia;
                break;

            case 'R':
                cabeca.x += distancia;
                break;
        }
        cauda->move(cabeca.x, cabeca.y);
    }

    void printResultado1() {
        int j{0};
        for (auto i : cauda->posi_visitadas) j++;
        std::cout << "Resposta 1: " << j << std::endl;
    };

    void printResultado2() {
        std::cout << "Resposta 2: " << cauda->resposta2() << std::endl;
    };

};

int Cauda::quantidade_de_caudas{0};

int main() {
    Corda corda;
    std::ifstream arquivo("input");

    std::string direcao, distancia;
    while (arquivo >> direcao >> distancia) {
        corda.move(direcao, distancia);
    }

    corda.printResultado1();
    corda.printResultado2();

}


