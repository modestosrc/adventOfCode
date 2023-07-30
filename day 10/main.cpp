#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Clock {
    int ciclo{1};
    int colunacrt{1};
    int linhacrt{0};
    int registrador{1};
    int resultado{0};
    array<int, 6> sinais{20, 60, 100, 140, 180, 220};
    array<array<char, 40>, 6> crt;


    void processaCrt(){
        if (colunacrt > 40) {colunacrt = 1; linhacrt++;}
        if (registrador - 1 <= colunacrt && colunacrt <= registrador + 1)
            crt[linhacrt][colunacrt-1] = '#';
        else
            crt[linhacrt][colunacrt-1] = '.';
        colunacrt++;
    }

    void processaSinal() {
        ciclo++;

        if (find(sinais.begin(), sinais.end(), ciclo) != sinais.end()) {
            resultado += ciclo * registrador;
        }
    }

    void sinal() {
        processaSinal();
        processaCrt();
    }

    void sinal(int x) {
        registrador += x;
        processaSinal();
        processaCrt();
    }

    public:

    void printResultado() {
        cout << "Resultado 1: " << resultado << endl;
    }

    void printCrt() {
        for (auto linha : crt) {
            for (char c : linha)
                cout << c;
            cout << endl;
        }
    }

    void comando(string str) {
        istringstream iss(str);
        int x;
        string com;
        if (iss >> com >> x) {
            sinal();
            sinal(x);
            return;
        } else {
            sinal();
            return;
        }
    }
};

int main(void) {
    Clock clock;
    ifstream arquivo("input");

    string str;
    while (getline(arquivo, str)) {
        clock.comando(str);
    }
    clock.printResultado();
    clock.printCrt();

}
