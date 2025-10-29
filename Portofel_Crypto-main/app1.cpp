#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "./shared/classes/Market.h"
#include "./shared/classes/Moneda.h"
#include "./shared/classes/Materiale.h"
#include "./shared/classes/Api.h"
#include "./shared/classes/Utils.h"

using namespace std;

string to_lower(const string& s) {
    string out = s;
    transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}
void init() {
    // Golește fișierul cu monede (sau îl creează gol dacă nu există)
    ofstream monedeFile("./shared/files/monede.txt", ios::trunc);
    monedeFile.close();

    // Golește fișierul cu materiale
    ofstream materialeFile("./shared/files/materiale.txt", ios::trunc);
    materialeFile.close();
}

// Scrie simbol într-un fișier (dacă nu există deja)
bool add_symbol(const string& filename, const string& simbol) {
    vector<string> symbols = load_items<string>(filename);
    if (find(symbols.begin(), symbols.end(), simbol) != symbols.end()) {
        return false; // deja există
    }
    ofstream outfile(filename, ios::app);
    if (!outfile) return false;
    outfile << simbol << "\n";
    outfile.close();
    return true;
}

// Șterge simbol din fișier
bool remove_symbol(const string& filename, const string& simbol) {
    vector<string> symbols = load_items<string>(filename);
    auto it = find(symbols.begin(), symbols.end(), simbol);
    if (it == symbols.end()) return false;
    symbols.erase(it);
    ofstream outfile(filename);
    if (!outfile) return false;
    for (auto& s : symbols) {
        outfile << s << "\n";
    }
    outfile.close();
    return true;
}

// Afișează toate activele (monede + materiale)
void view_assets() {
    vector<string> monede = load_items<string>("./shared/files/monede.txt");
    vector<string> materiale = load_items<string>("./shared/files/materiale.txt");

    vector<Market*> portofoliu;
    for (auto& sim : monede) portofoliu.push_back(new Moneda(sim));
    for (auto& sim : materiale) portofoliu.push_back(new Material(sim));

    cout << "Simbol - Pret (RON)\n";
    for (auto p : portofoliu) {
        cout << p->getSimbol() << " - " << p->getPret() << "\n";
    }

    for (auto p : portofoliu) delete p;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Comanda invalida. Formate posibile:\n"
             << "adaugare_moneda <simbol>\n"
             << "stergere_moneda <simbol>\n"
             << "adaugare_material <simbol>\n"
             << "stergere_material <simbol>\n"
             << "vizualizare\n";
        return 1;
    }

    string cmd = argv[1];
    if (cmd == "init") {
        init();
        std::cout << "Fisierele monede si materiale au fost resetate.\n";
        return 0;
    }

    if (cmd == "vizualizare") {
        view_assets();
        return 0;
    }

    if (argc < 3) {
        cout << "Lipseste simbolul. Utilizare corecta:\n"
             << cmd << " <simbol>\n";
        return 1;
    }

    string simbol = argv[2];

    if (cmd == "adaugare_moneda") {
        if (add_symbol("./shared/files/monede.txt", simbol))
            cout << "Moneda " << simbol << " adaugata.\n";
        else
            cout << "Moneda " << simbol << " exista deja sau eroare.\n";
    }
    else if (cmd == "stergere_moneda") {
        if (remove_symbol("./shared/files/monede.txt", simbol))
            cout << "Moneda " << simbol << " stearsa.\n";
        else
            cout << "Moneda " << simbol << " nu exista.\n";
    }
    else if (cmd == "adaugare_material") {
        if (add_symbol("./shared/files/materiale.txt", simbol))
            cout << "Material " << simbol << " adaugat.\n";
        else
            cout << "Material " << simbol << " exista deja sau eroare.\n";
    }
    else if (cmd == "stergere_material") {
        if (remove_symbol("./shared/files/materiale.txt", simbol))
            cout << "Material " << simbol << " sters.\n";
        else
            cout << "Material " << simbol << " nu exista.\n";
    }
    else {
        cout << "Comanda necunoscuta.\n";
        return 1;
    }

    return 0;
}
