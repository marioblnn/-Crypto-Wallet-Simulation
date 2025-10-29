#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include "Market.h"

Market* createMarketFromSimbol(const std::string& simbol);

// Funcție template pentru încărcarea oricărui tip T dintr-un fișier text (cuvinte separate prin spațiu / newline)
template <typename T>
vector<T> load_items(const string& filename) {
    vector<T> items;
    ifstream infile(filename);
    if (!infile) return items;

    T item;
    while (infile >> item) {
        items.push_back(item);
    }
    return items;
}

#endif
