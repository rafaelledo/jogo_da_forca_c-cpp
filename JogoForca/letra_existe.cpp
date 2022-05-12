#include <string>

bool letra_existe (char chute, std::string palavra_secreta) {
    for (char letra : palavra_secreta) {
        if (chute == letra) {
            return true;
        }
    }
    return false;
}