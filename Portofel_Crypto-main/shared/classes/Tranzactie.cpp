#include "Tranzactie.h"

Tranzactie::Tranzactie(std::string s, double c, double p)
    : simbol(s), cantitate(c), pret(p) {}

std::string Tranzactie::getSimbol() const {
    return simbol;
}
double Tranzactie::getCantitate() const {
    return cantitate;
}
double Tranzactie::getPret() const {
    return pret;
}
ostream& operator<<(ostream& out, const Tranzactie& t) {
    out << "Cumparat " << t.cantitate << " " << t.simbol << " cu ";
    return out;
}