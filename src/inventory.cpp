#include "inventory.h"
#include <iomanip>

std::vector<Items*> Inventory::getInventory()
{
    return inventory;
}

double Inventory::getBalance()
{
    return money;
}
void Inventory::changeBalance(float ammount)
{
    money += ammount;
}

int Inventory::getInventorySize()
{
    return inventory.size();
}
float Inventory::getItemPrice(int id)
{
    return inventory.at(id)->getPrix();
}
int Inventory::getAmmount(int id)
{
    return inventory.at(id)->getAmmount();
}

void Inventory::clear()
{
    for(int i=0; i< inventory.size(); i++)
        if(inventory.at(i)->getAmmount()<=0)  //if there isn't any item left...
            inventory.erase(inventory.begin() + i); //remove the item from the list
}

void Inventory::addItem(std::string nom , float prix , int ammount)
{
    bool present = false;
    for(Items* i : inventory)   //regarde si l'item est présent dans la liste
        if(i->getName() == nom) //si l'item à le même nom...
        {
            present = true;     
            i->addItem(ammount);    //ajoute l'item
            break;
        }
    if(!present)
        inventory.push_back(new Items(nom, prix, ammount));
}
void Inventory::addItem(Items* item, int ammount)
{
    bool present = false;
    for(Items* i : inventory)   //regarde si l'item est présent dans la liste
        if(i->getName() == item->getName()) //si l'item à le même nom...
        {
            present = true;     
            i->addItem(ammount);    //ajoute l'item
            break;
        }
    if(!present)
        inventory.push_back(new Items(item->getName(), item->getPrix(), 1));
}

void Inventory::printInventory()
{
    printf("\033[%d;0H", g_map[0]+1);   //met le curseur en bas de la carte
    for(Items* i : this->getInventory())   //print the inventory
    {
        std::cout << std::setw(15) << i->getName() << ", " << std::setw(5)<< i->getAmmount()<<"\r\n";
    }
    fflush(stdout);
}
void Inventory::printInventoryABC()
{
    char invPosition=97;
    printf("\033[%d;0H", g_map[0]+1);   //met le curseur en bas de la carte
    for(Items* i : this->getInventory())   //print the inventory
    {
        std::cout << invPosition << std::setw(15) << i->getName() << " , " << std::setw(5) 
        << i->getPrix() << "$ | " << i->getAmmount()<<"\r\n";//invPosition + 97 -> ASCII position
        invPosition++;
    }
    std::cout << "q - quitter\r\n";
    fflush(stdout);
}
void Inventory::printInventoryA()      //doesn't show the price
{
    printf("\033[%d;0H", g_map[0]+1);   //met le curseur en bas de la carte
    for(Items* i : this->getInventory())   //print the inventory
    {
        std::cout << std::setw(15) << i->getName() << " , " << std::setw(5) 
        << i->getPrix() << "$\r\n";
    }
    std::cout << std::string(g_map[1], '-') << "\r\n";
}
void Inventory::printInventoryB()      //doesn't show the price
{
    char invPosition=97;
    for(Items* i : this->getInventory())   //print the inventory
    {
        std::cout << invPosition << std::setw(15) << i->getName() << " , " << std::setw(5) 
        << i->getAmmount() << "\r\n";
        invPosition++;
    }
    std::cout << "q - quitter\r\n";
    fflush(stdout);
}

Items* Inventory::removeItem(int id)
{
    inventory.at(id)->removeItem(1);
    return inventory.at(id);
}

void Inventory::clearItem(int id)
{
    inventory.erase(inventory.begin() + id);
}