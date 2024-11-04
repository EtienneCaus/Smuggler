#pragma once
#include <iostream>

extern const int g_map[2];  //importe la hauteur & largeur de la carte

class Entity
{
protected:
    int position[2]={0,0};  //position Y, X
    char character=0;       //graphique de l'entité
    std::string entityColour = "\033[0m"; //la couleur(ici BLANC)
    void initiate(int y, int x, char c);
    void initiate(int y, int x, char c, std::string s);

public:             //méthodes:
    void print();
    int getPositionY();
    int getPositionX();
    void move(int y, int x);
};