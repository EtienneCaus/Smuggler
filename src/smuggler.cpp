#include "entity.h"
#include "inventory.h"

class Smuggler : public Entity
{
    float getCaughtChances=0;
    int gotCaughtX=0;
public:
    Inventory inventaire;   //l'inventaire; doit être public

    Smuggler(int y, int x, char c, double d)
    {
        inventaire.changeBalance(d);  //initialise la balance de départ
        initiate(y,x,c);    //initiate without colour (white)
    }

    Smuggler(int y, int x, char c, double d, std::string s)
    {
        inventaire.changeBalance(d);  //initialise la balance de départ
        initiate(y,x,c,s);  //initiate with colour
    }
    void setPosition(int y, int x)
    {
        this->position[0]=y;
        this->position[1]=x;
    }

    float CheckCaught()
    {
        getCaughtChances=0;
        for(Items* i : inventaire.getInventory())
        {
            getCaughtChances += i->getAmmount()*4;  //augmente les chances de se faire
        }                  //prendre, plus l'on a d'objets, plus les chances augmentes
        return getCaughtChances;
    }
    bool gotCaught()
    {
        inventaire.changeBalance(-100-(50*gotCaughtX)); //remove 100+ money
        std::cout << "\rVous vous êtes fait prendre et devez payer un\r\n" << 
                            "pot-de-vin à la police pour vous en sortir\r\n";
        std::cout << "( -"<<  (100+(50*gotCaughtX)) << "$ )\r\n";
        std::cout << "La police a réquisitionné certains de vos items";
        inventaire.clearItem(rand()%inventaire.getInventorySize()); //clear random items
        gotCaughtX++;   //augmente le nombre de fois que l'on s'est fait prendre
        std::cin.ignore();
        std::cin.get(); //pause
        if(inventaire.getBalance()>=0)
            return false;
        else
            return true;
    }
};