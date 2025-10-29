#pragma once
#include <string>
#include <iostream>
using namespace std;

class Tranzactie {
private:
    std::string simbol;
    double cantitate;
    double pret;
public:
    Tranzactie(std::string s, double c, double p);
    std::string getSimbol() const;
    double getCantitate() const;
    double getPret() const;
    friend ostream& operator<<(ostream& out, const Tranzactie& t);
};
