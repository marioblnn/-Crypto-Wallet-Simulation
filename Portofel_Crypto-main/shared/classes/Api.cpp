#include "Api.h"
#include <cmath>
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <json/json.h> 
#include <algorithm>
using namespace std;

double Api::getMetalPrice(const string& metal) {
    double price = 0.0;
    for (char c : metal) price += (int)c;
    // Generează un preț între 1 și 500 RON per gram, determinist
    price = fmod(price * 37, 500) + 1; 
    return price;
}
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

double Api::getPriceFromApi(const std::string& simbol, const std::string& fiat) {
    string simbol_lower = simbol;
    transform(simbol_lower.begin(), simbol_lower.end(), simbol_lower.begin(), ::tolower);

    CURL* curl;
    CURLcode res;
    string readBuffer;
    string url = "https://api.coingecko.com/api/v3/simple/price?ids=" + simbol_lower + "&vs_currencies=" + fiat;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res == CURLE_OK) {
            Json::Value jsonData;
            Json::CharReaderBuilder builder;
            string errs;
            istringstream s(readBuffer);
            if (Json::parseFromStream(builder, s, &jsonData, &errs)) {
                if (jsonData[simbol_lower][fiat].isNumeric())
                    return jsonData[simbol_lower][fiat].asDouble();
            }
        }
    }
    return -1.0; // Eroare
}