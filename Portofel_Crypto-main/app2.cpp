#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "./shared/classes/Market.h"
#include "./shared/classes/Materiale.h"
#include "./shared/classes/Moneda.h"
#include "./shared/classes/Tranzactie.h"
#include "./shared/classes/Api.h"
#include "./shared/classes/Portofoliu.h"
#include "./shared/classes/Utils.h"
using namespace std;

void init_wallet(double suma) {
    // 1. Scrie suma în fonduri.txt
    ofstream fout("./shared/files/fonduri.txt");
    if (!fout) {
        cerr << "Eroare la scrierea in fonduri.txt\n";
        return;
    }
    fout << suma << "\n";
    fout.close();

    // 2. Șterge portofelul (wallet.txt)
    ofstream wallet_out("./shared/files/wallet.txt", ios::trunc);
    wallet_out.close();

    // 3. Șterge tranzacțiile (tranzactii.txt)
    ofstream tranzactii("./shared/files/tranzactii.txt", ios::trunc);
    tranzactii.close();

    cout << "Portofel resetat complet. Fonduri disponibile: " << suma << " RON.\n";
}

// Functie pentru cumpararea unei monede
void buy_coin(const string& simbol, double sumaRON) {

    // Verifică fonduri disponibile
    if (sumaRON > Portofoliu::getSumaDisponibila()) {
        cout << "Fonduri insuficiente. Ai doar " << Portofoliu::getSumaDisponibila() << " RON disponibili.\n";
        return;
    }
    // verifica dacă simbolul există în fișiere
    bool found = false;
    ifstream infile("./shared/files/monede.txt");
    string line;
    while (infile >> line) {
        if (line == simbol) {
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        // dacă nu e moneda, verifică în materiale
        ifstream infile2("./shared/files/materiale.txt");
        while (infile2 >> line) {
            if (line == simbol) {
                found = true;
                break;
            }
        }
        infile2.close();
    }

    if (!found) {
        cout << "Simbolul " << simbol << " nu exista in lista.\n";
        return;
    }

    // obiectul Market corespunzator
    Market* asset = createMarketFromSimbol(simbol);
    if (!asset) {
        cout << "Eroare la creare obiect pentru simbol.\n";
        return;
    }

    double price = asset->getPret();

    double qty = sumaRON / price;
    if (qty <= 0) {
        cout << "Suma invalida.\n";
        delete asset;
        return;
    }

    auto wallet = Portofoliu::load();
    bool exists = false;
    for (auto &p : wallet) {
        if (p.first == simbol) {
            p.second += qty;
            exists = true;
            break;
        }
    }
    if (!exists) {
        wallet.push_back({simbol, qty});
    }
    Portofoliu::save(wallet);

    // Scade suma investită din suma disponibila
    Portofoliu::setSumaDisponibila(Portofoliu::getSumaDisponibila() - sumaRON);

    Tranzactie t(simbol, qty, price);
    Portofoliu::appendTranzactie(t);

    cout << t << sumaRON << " RON (pret " << price << " RON)\n";

    delete asset;
}

// Afiseaza tranzactiile
void view_tranzactii() {
    ifstream infile("./shared/files/tranzactii.txt");
    if (!infile) {
        cout << "Nu exista tranzactii.\n";
        return;
    }
    cout << "Tranzactii:\nSimbol - Cantitate - Pret(RON)\n";
    string simbol;
    double cant, pret;
    while (infile >> simbol >> cant >> pret) {
        cout << simbol << " - " << cant << " - " << pret << "\n";
    }
    infile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Comanda invalida. Comenzi posibile: init, cumparare, vizualizare_portofel, vizualizare_tranzactii, export\n";
        return 1;
    }

    string cmd = argv[1];

    if (cmd == "init") {
        if (argc != 3) {
            cout << "Utilizare: init <sumaRON>\n";
            return 1;
        }
        double suma = atof(argv[2]);
        init_wallet(suma);
    } else if (cmd == "cumparare") {
        if (argc != 4) {
            cout << "Utilizare: cumparare <simbol> <sumaRON>\n";
            return 1;
        }
        string simbol = argv[2];
        double sumaRON = atof(argv[3]);
        buy_coin(simbol, sumaRON);
    } else if (cmd == "vizualizare_portofel") {
        Portofoliu::view();
    } else if (cmd == "vizualizare_tranzactii") {
        view_tranzactii();
    } else if (cmd == "export") {
        Portofoliu::exportCSV();
    } else {
        cout << "Comanda necunoscuta.\n";
        return 1;
    }

    return 0;
}