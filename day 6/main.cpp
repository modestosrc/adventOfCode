#include <array>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#define TAMANHO 14

bool checaArr(std::array<char, TAMANHO> arr) {
    for (int i{0}; i < arr.size(); i++)
        for (int j{arr.size() - 1}; j > i; j--)
            if (arr[i] == arr[j]) return false;
    return true;
}

void modArr(std::array<char, TAMANHO> &arr, char newChar) {
    for (int i{0}; i < arr.size() - 1; i++)
        arr[i] = arr[i + 1];
    *(arr.end() - 1) = newChar;

    //for (int j{0}; j < TAMANHO; j++)
    //    std::cout << arr[j] << ' ';
    //std::cout << std::endl;
}

int main() {
    std::ifstream arquivo("input");

    std::array<char, TAMANHO> arr{};
    std::string s;
    int i{0};
    while (std::getline(arquivo, s)) {
        for (char c : s) {
            modArr(arr, c);
            i++;
            if (checaArr(arr))
                goto FIM;
        }
    }

    return 1;
FIM:
    std::cout << "Resposta: " << i << std::endl;
    return 0;
}
