#pragma once
#include <string>
#include <vector>
#include "Tranzactie.h"

class Portofoliu {
public:
    static std::vector<std::pair<std::string, double>> load();
    static void save(const std::vector<std::pair<std::string, double>>& wallet);
    static void appendTranzactie(const Tranzactie& t);
    static void view();
    static void exportCSV();

    static double sumaDisponibila;
    static double loadSumaDisponibila();
    static void saveSumaDisponibila();
    static double getSumaDisponibila();
    static void setSumaDisponibila(double suma);
};
