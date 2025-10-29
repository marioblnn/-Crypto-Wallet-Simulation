#include "Portofoliu.h"
#include "Api.h"
#include "Market.h"
#include "Materiale.h"
#include "Moneda.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

vector<pair<string,double>> Portofoliu::load() {
    vector<pair<string,double>> wallet;
    ifstream infile("./shared/files/portofel.txt");
    if (!infile) return wallet;
    string simbol;
    double cant;
    while(infile >> simbol >> cant) {
        wallet.push_back({simbol, cant});
    }
    infile.close();
    return wallet;
}

void Portofoliu::save(const vector<pair<string,double>>& wallet) {
    ofstream outfile("./shared/files/portofel.txt");
    for (auto &p : wallet) {
        outfile << p.first << " " << p.second << "\n";
    }
    outfile.close();
}

void Portofoliu::appendTranzactie(const Tranzactie& t) {
    ofstream outfile("./shared/files/tranzactii.txt", ios::app);
    if (!outfile) return;
    outfile << t.getSimbol() << " " << t.getCantitate() << " " << t.getPret() << "\n";
    outfile.close();
}

void Portofoliu::view() {

    auto wallet = load();
    double sumaDisponibila = getSumaDisponibila();

    if (wallet.empty()) {
        cout << "Portofoliu gol.\n";
        cout << "Fonduri disponibile pentru investitii: " << sumaDisponibila << " RON\n";
        return;
    }

    double valoareInvestita = 0;
    cout << "Portofoliu:\nSimbol - Cantitate - ValoareCurenta(RON)\n";

    for (auto &p : wallet) {
        double price = Api::getPriceFromApi(p.first, "ron");
        double valoare = p.second * price;
        valoareInvestita += valoare;
        cout << p.first << " - " << p.second << " - " << valoare << "\n";
    }

    cout << "Valoare totala investita in portofoliu: " << valoareInvestita << " RON\n";
    cout << "Fonduri disponibile pentru investitii: " << sumaDisponibila << " RON\n";
    cout << "Valoare totala portofoliu + fonduri disponibile: " << valoareInvestita + sumaDisponibila << " RON\n";
}

void Portofoliu::exportCSV() {
    auto wallet = load();
    if (wallet.empty()) {
        cout << "Portofel gol, nimic de exportat.\n";
        return;
    }
    ofstream csv("./shared/files/portofel.csv");
    if (!csv) {
        cout << "Eroare la crearea fisierului portofel.csv\n";
        return;
    }
    csv << "Simbol,Cantitate,PretCurentRON,ValoareRON\n";
    for (auto &p : wallet) {
        double price = Api::getPriceFromApi(p.first, "ron");
        double value = p.second * price;
        csv << p.first << "," << p.second << "," << price << "," << value << "\n";
    }
    csv.close();
    cout << "Portofel exportat in portofel.csv\n";
}

// Inițializare variabilă statică
double Portofoliu::sumaDisponibila = Portofoliu::loadSumaDisponibila();

double Portofoliu::loadSumaDisponibila() {
    ifstream fin("./shared/files/fonduri.txt");
    double suma = 10000.0;  // valoare default dacă nu există fișierul
    if (fin >> suma) {
        return suma;
    }
    return 10000.0;
}

void Portofoliu::saveSumaDisponibila() {
    ofstream fout("./shared/files/fonduri.txt");
    fout << sumaDisponibila;
    fout.close();
}

double Portofoliu::getSumaDisponibila() {
    return sumaDisponibila;
}

void Portofoliu::setSumaDisponibila(double suma) {
    sumaDisponibila = suma;
    saveSumaDisponibila();  // salvează automat după schimbare
}