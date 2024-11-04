#include "items.h"
#include <iostream>

Items::Items(std::string nom, float prix, int ammount)
{
    this->nom = nom;
    this->prix = prix;
    this->ammount = ammount;
}
Items::Items(std::string nom, float prix)
{
    this->nom = nom;
    this->prix = prix;
}
Items::Items(Items* item, int ammount)
{
    this->nom = item->nom;
    this->prix = item->prix;
    this->ammount = ammount;
}
Items::Items(Items* item)
{
    this->nom = item->nom;
    this->prix = item->prix;
    this->ammount = item->ammount;
}

void Items::addItem(int ammount)
{
    this->ammount += ammount;
}
void Items::removeItem(int ammount)
{
    this->ammount -= ammount;
}

std::string Items::getName()
{
    return nom;
}
float Items::getPrix()
{
    return prix;
}
int Items::getAmmount()
{
    return ammount;
}