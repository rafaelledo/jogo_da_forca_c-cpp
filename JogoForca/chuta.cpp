#include <iostream>
#include "chuta.hpp"
#include "letra_existe.hpp"

void Forca::chuta (std::map<char, bool>& chutou, std::array<char, 5>& chutes_errados, int& num_chutes_errados, std::string& palavra_secreta) {
    std::cout << "Seu chute: ";
    char chute;
    std::cin >> chute;

    chutou[chute] = true;

    if (letra_existe(chute, palavra_secreta)) {
        std::cout << "Chute está na palavra" << std::endl;
    }
    else {
        std::cout << "Chute não está na palavra" << std::endl;
        chutes_errados[num_chutes_errados++] = chute;
    }
    std::cout << std::endl;
}