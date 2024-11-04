#pragma once
#include "items.h"
#include <vector>

extern const int g_map[2];  //importe la hauteur & largeur de la carte

class Inventory
{
    double money=0;
    std::vector<Items*> inventory;    

public:
    std::vector<Items*> getInventory();
    double getBalance();
    void changeBalance(float ammount);
    int getInventorySize();
    int getAmmount(int id);
    float getItemPrice(int id); 
    void clear();   
    void addItem(std::string nom , float prix , int ammount);
    void addItem(Items* item, int ammount);
    void printInventory();
    void printInventoryABC();
    void printInventoryA();
    void printInventoryB();
    Items* removeItem(int id);
    void clearItem(int id);
};