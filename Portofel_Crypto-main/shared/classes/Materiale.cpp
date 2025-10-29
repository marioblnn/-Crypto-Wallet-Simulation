#include "Materiale.h"
#include "Api.h"

double Material::getPret() const {
    return Api::getMetalPrice(simbol); // preț pe gram
}
string Material::getSimbol() const {
    return simbol;
}