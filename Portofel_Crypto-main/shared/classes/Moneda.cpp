#include "Moneda.h"


string Moneda::getSimbol() const {
    return simbol;
}
double Moneda::getPret() const {
    return Api::getPriceFromApi(simbol, "ron");
}