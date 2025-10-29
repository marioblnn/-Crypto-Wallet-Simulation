#include "Utils.h"
#include "Materiale.h"
#include "Moneda.h"

Market* createMarketFromSimbol(const std::string& simbol) {
    if (simbol == "aur" || simbol == "argint" || simbol == "cupru" || simbol == "uraniu" || simbol == "fier") {
        return new Material(simbol);
    } else {
        return new Moneda(simbol);
    }
}
