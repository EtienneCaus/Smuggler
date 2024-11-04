#include "entity.h"
#include <iostream>

void Entity::print()
{
    printf("\033[%d;%dH", position[0], position[1]);    //put the cursor at position Y, X
    std::cout << entityColour;            //chage the colour
    printf("%c", character);                //print the character
    std::cout << "\033[0m";//put the color back to white
};

int Entity::getPositionY()
{
    return position[0];
}
int Entity::getPositionX()
{
    return position[1];
}

void Entity::initiate(int y, int x, char c) //needed to initiate entities
{
    position[0] = y;
    position[1] = x;
    character = c;
}

void Entity::initiate(int y, int x, char c, std::string s)
{
    position[0] = y;
    position[1] = x;            //initiate with custom colour
    character = c;
    entityColour = s;
}

void Entity::move(int y, int x) //move the entities
{
    if(position[0]+y > 0 && position[0]+y <= g_map[0]) //regarde si la
        position[0] += y;           //nouvelle position ne dépasse pas le
    if(position[1]+x > 0 && position[1]+x <= g_map[1]) //tableau
        position[1] += x;
}