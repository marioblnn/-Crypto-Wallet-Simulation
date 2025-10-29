#pragma once
#include "Market.h"
#include "Api.h"

class Material : public Market {
    string simbol;
public:
    Material(const string& s) : simbol(s) {}
    string getSimbol() const override;
    double getPret() const override;
};