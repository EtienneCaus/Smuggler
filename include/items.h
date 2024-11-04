#pragma once
#include <iostream>
#include <map>

struct Items
{
    std::string nom="";
    float prix=0;
    int ammount=0;

public:
    Items(std::string nom, float prix, int ammount);
    Items(std::string nom, float prix);
    Items(Items* item, int ammount);
    Items(Items* item);
    void addItem(int ammount);
    void removeItem(int ammount);
    std::string getName();
    float getPrix();
    int getAmmount();
};