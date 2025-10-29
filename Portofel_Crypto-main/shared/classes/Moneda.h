#pragma once
#include <string>
#include <iostream>
#include "Market.h"
#include "Api.h"
using namespace std;

class Moneda : public Market {
    string simbol;
public:
    Moneda(const string& s) : simbol(s) {}
    string getSimbol() const override;
    double getPret() const override;
};
