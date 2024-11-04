#include <iostream>
#include <list>
#include "inventory.h"
#include "entity.h"
using namespace std;

class City : public Entity
{
    std::string name="";

public:
    Inventory inventaire;
    void generateItems()    //génère l'inventaire de la ville
    {    
        inventaire.addItem("contrebande", rand()%100+60, rand()%10);  
        inventaire.addItem("drogues", rand()%80+80, rand()%10);       
        inventaire.addItem("armes", rand()%20+200, rand()%10);          
        inventaire.addItem("bijoux", rand()%40+120, rand()%10);           
        inventaire.addItem("materiaux", rand()%200, rand()%10);
    }
    
    City(int y, int x, char c, std::string s)
    {
        inventaire.changeBalance(rand()%1000+100);  //initialise la balance de départ
        generateItems();
        initiate(y,x,c);  //initiate without colour
        this->name = s;
    }
    City(int y, int x, char c, std::string s, std::string col)
    {
        inventaire.changeBalance(rand()%10000+1000);  //nombre au hazard de 1000 à 10999
        generateItems();
        initiate(y,x,c,col);  //initiate with colour
        this->name = s;
    }

    std::string getName()
    {
        return name;
    }

    void show()
    {
        printf("\033[%d;%dH", position[0], position[1]);//put the cursor at position Y, X
        std::cout << entityColour;            //chage the colour
        std::cout << name;                //print the name
        std::cout << "\033[0m";//put the color back to white
    }
};