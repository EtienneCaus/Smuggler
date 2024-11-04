#include <iostream>
#include <vector>
#include <curses.h>
#include "smuggler.cpp"
#include "city.cpp"
#include "colour.h"

using namespace std;

bool running = true; //check if the program is running
int refill=0;   //refill cities inventory after X turns
const int g_map[2]={25,50};    //hauteur et largeur de la carte
vector<City*> cities;   //liste(pointeur) des villes    
Smuggler *smuggler = new Smuggler(15,13,'@', 400 ,colour["yellow"]);  //crée le contrebandier

void ville(City* ville);
void lost();
void printScreen()
{
    cout << colour["clears"]; // clears screen
    for(int y=0; y<=g_map[0]; y++)
        printf("\033[%d;%dH%c", y , g_map[1]+1, '|'); //imprimme le bord du tableau
    for(City* c : cities)
        c->print();
    smuggler->print();
};

int main()
{
    initscr();              //initialise l'écran
    refresh();//refresh the screen (so that getch() won't clear screen the first time)
    keypad(stdscr, TRUE);   //for using keypad
    curs_set(0);            //hide the cursor

    cities.push_back(new City(18,22,'#', "Montréal", colour["blue"]));  //met une ville
    cities.push_back(new City(12,38,'#', "Québec", colour["blue"]));
    cities.push_back(new City(19,14,'#', "Ottawa", colour["red"]));
    cities.push_back(new City(20,34,'#', "Sherbrooke"));
    cities.push_back(new City(16,32,'#', "Trois-Rivières"));
    cities.push_back(new City(9,4,'#', "Val-d'Or"));
    cities.push_back(new City(8,39,'#', "Saguenay"));           //met plusieurs villes

    while(running)
    {
        printScreen();
        printf("\033[%d;0H", g_map[0]+1);   //met le curseur en bas du tableau
        cout << string(g_map[1],'~') << "+\r";
        cout << "\ni - inventaire\r\nl - regarder\r\n";
        for(City* c : cities)
            if(c->getPositionX() == smuggler->getPositionX() && //si l'on est sur une ville...
                c->getPositionY() == smuggler->getPositionY())
                cout << "f - entrer dans une ville";    //...imprimme ceci
        cout << "\r\nq - quitter\r\n";

        if(refill++ > 100)  //regarde si le nbr de pas depuis le dernier réaprovisonement
        {
            for(City* c : cities)
            {
                c->generateItems(); //réaprovisionne les villes
                refill = 0;
            }
            cout << "Les villes ont été réaprovisionné";
        }
        fflush(stdout); //needed to print stuff

        switch (int input = getch())  //get user input
        {
        case KEY_UP:    //si l'input est la flèche du haut...
            smuggler->move(-1,0);   //...bouge le contrebandier en haut
        break;
        case KEY_LEFT:
            smuggler->move(0,-1);   //..à gauche..
        break;
        case KEY_DOWN:
            smuggler->move(1,0);    //..en bas..
        break;
        case KEY_RIGHT:
            smuggler->move(0,1);    //..à droite
        break;
        case 'f':
        for(City* c : cities)
            if(c->getPositionX() == smuggler->getPositionX() &&
                    c->getPositionY() == smuggler->getPositionY())
            {
                ville(c);   //appel la méthode ville
                break;
            }                                   
        break;
        case 'i':
            printScreen();
            printf("\033[%d;0H", g_map[0]);
            cout << string(g_map[1],'~') << "+\r";
            cout << smuggler->inventaire.getBalance() << " $\r\n";
            smuggler->inventaire.printInventory();  //imprime l'inventaire du contrebandier
            cout << smuggler->CheckCaught() << "% chance de se faire prendre";
            fflush(stdout); 
            input = getch();
        break;
        case 'l':
            printScreen();
            printf("\033[%d;0H", g_map[0]+1);
            cout << string(g_map[1],'~') << "+\r";
            for(City* c : cities)
                c->show();  //montre le nom des villes
            fflush(stdout); 
            timeout(1000);  //give a certain amount of time before skipping user input
            input = getch();
            timeout(-1);    //remove the timeout (won't skip user input)
        break;
        case 'q':
            running = false;        //ends the program
        break;
        }
    }

    for (Items *i : smuggler->inventaire.getInventory())
        delete i;   //détruit l'inventaire du contrebandier
    delete smuggler;//détruit le contrebandier
    for(City *c : cities)
    {
        for (Items *i : c->inventaire.getInventory())
            delete i;   //détuit l'innventaire de la ville
        delete c;   //détruit toute les villes dans la liste
    }
    cities.clear();   //efface la liste "entités"

    endwin();   //end the uses of ncurses
    return 0;
}

void ville(City* ville)            //Lorsqu'on entre dans une ville...
{
    bool inCity=true;
    if(smuggler->CheckCaught()>rand()%100)  //si le contrebandier se fait prendre
    {
        inCity = false;
        int randomcity=0; 
        while(randomcity != -1)
        {
            randomcity=rand()%cities.size();//change the position of smuggler to random city
            if(smuggler->getPositionY() != cities.at(randomcity)->getPositionY() ||
                smuggler->getPositionX() != cities.at(randomcity)->getPositionX())
            {
                smuggler->setPosition(cities.at(randomcity)->getPositionY(),
                            cities.at(randomcity)->getPositionX());
                randomcity=-1;  //regarde si le contrebandier est à la nouvelle ville, et quitte        
            }     
        }
        if(smuggler->gotCaught())   //si l'on a moins de 0$ àprès s'être fait prendre
            lost();
    }
    while(inCity)
    {
        printScreen();
        printf("\033[%d;0H", g_map[0]+1);   //met le curseur en bas de la carte
        cout << string(g_map[1],'~') << "+\r";
        cout << "Bienvenu à " << ville->getName() << endl;
        cout << "\r\n1 - Acheter\r\n2 - Vendre\r\n3 - Quitter";
        fflush(stdout);             //affiche menu des villes

        bool shopping=true;
        switch(int input = getch()) //ask user input
        {
            case '1':
                while(shopping)     //Achète...
                {
                    printScreen();
                    printf("\033[%d;0H", g_map[0]);
                    cout << string(g_map[1],'~') << "+\r";
                    cout << smuggler->inventaire.getBalance() << " $\r\n";
                    ville->inventaire.printInventoryABC();  //imprime l'inventaire de la ville
                    input = getch();
                    if(input == 'q')
                        shopping=false;
                    else
                    {
                        input -= 'a';//put the input to numerical value
                        if(input >=0 && input <ville->inventaire.getInventorySize()//si l'inventaire existe
                            && smuggler->inventaire.getBalance() >= ville->inventaire.getItemPrice(input)
                            && ville->inventaire.getAmmount(input)) //...et que l'on a assé d'argent..
                        {                                          //...et aussi que la ville à cet item
                            smuggler->inventaire.changeBalance((ville->inventaire.getItemPrice(input))*-1);
                            ville->inventaire.changeBalance((ville->inventaire.getItemPrice(input)));
                            smuggler->inventaire.addItem(ville->inventaire.removeItem(input),1);
                        }
                        fflush(stdout);
                    }
                        
                }
            break;
            case '2':
                while(shopping) //Vends...
                {
                    printScreen();
                    printf("\033[%d;0H", g_map[0]);
                    cout << string(g_map[1],'~') << "+\r";
                    cout << ville->inventaire.getBalance() << " $\r\n";
                    ville->inventaire.printInventoryA();    //imprime l'inventaire de la ville
                    smuggler->inventaire.printInventoryB(); //imprime l'inventaire du contrebandier
                    input = getch();
                    if(input == 'q')
                        shopping=false;
                    else
                    {
                        input -= 'a';//put the input to numerical value
                        if(input >=0 && input <smuggler->inventaire.getInventorySize()
                            && ville->inventaire.getBalance() >= ville->inventaire.getItemPrice(input))
                        {   //si l'objet se trouve dans l'inventaire du contrebandier...
                            ville->inventaire.changeBalance((ville->inventaire.getItemPrice(input))*-1);
                            smuggler->inventaire.changeBalance((ville->inventaire.getItemPrice(input)));
                            ville->inventaire.addItem(smuggler->inventaire.removeItem(input),1);
                            smuggler->inventaire.clear();
                        }//vends (et transfert) l'objet à la ville au prix de la ville
                        fflush(stdout);
                    }
                }
            break;
            case '3':
            inCity=false;   //quitte la ville
            break;
        }   
    }
}

void lost()
{
    printScreen();
    printf("\033[%d;0H", g_map[0]+1);   //met le curseur en bas du tableau
    cout << "Vous ne pouvez pas payer le pot-de-vin et la police\r\nvous a mis en prison :(\r\n";
    cout << "\r\nPARTIE TERMINÉ!\r\n";
    getch();
    running = false;    //sort du jeu
}