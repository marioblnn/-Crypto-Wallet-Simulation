#pragma once
#include <string>

class Api {
public:
    static double getMetalPrice(const std::string&);
    static double getPriceFromApi(const std::string& simbol, const std::string& fiat = "ron");
};