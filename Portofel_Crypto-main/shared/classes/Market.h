#pragma once
#include <string>
#include <iostream>
using namespace std;

class Market {
public:
    virtual ~Market() = default;
    virtual string getSimbol() const = 0;
    virtual double getPret() const = 0;
};