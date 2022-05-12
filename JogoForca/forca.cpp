#include <iostream>
#include <string>
#include <map>
#include <array>

#include "nao_acertou.hpp"
#include "letra_existe.hpp"
#include "le_arquivo.hpp"
#include "imprime_cabecalho.hpp"
#include "sorteia_palavra.hpp"
#include "nao_acertou.hpp"
#include "imprime_erros.hpp"
#include "imprime_palavra.hpp"
#include "chuta.hpp"
#include "adiciona_palavra.hpp"

static std::string palavra_secreta;
static std::map<char, bool> chutou;
static std::array<char, 5> chutes_errados;
static int num_chutes_errados = 0;

int main () {
    
    imprime_cabecalho();

    palavra_secreta = sorteia_palavra();

    while (nao_acertou(palavra_secreta, chutou) && num_chutes_errados < 5) {
        Forca::imprime_erros(chutes_errados, num_chutes_errados);

        Forca::imprime_palavra(palavra_secreta, chutou);

        Forca::chuta(chutou, chutes_errados, num_chutes_errados, palavra_secreta);
    }

    std::cout << "Fim de jogo" << std::endl;
    std::cout << "Palavra secreta: " << palavra_secreta << std::endl;
    if (nao_acertou(palavra_secreta, chutou)) {
        std::cout << "Você perdeu" << std::endl;
    }
    else {
        std::cout << "Você acertou!" << std::endl;

        std::cout << "Quer adicionar uma nova palavra ao banco? (S/N) ";
        char resposta;
        std::cin >> resposta;
        if (resposta == 'S') {
            Forca::adiciona_palavra();
        }
    }

}