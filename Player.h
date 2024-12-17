#ifndef PLAYER_H
#define PLAYER_H
#include "Room.h"
#include "Creature.h"
#include "Item.h"

#define INVENTORY_CAPACITY 10

typedef struct{
char* name;    
int health;
int strength;
Item **inventoryA; 
int inventoryCount;
Room* currentRoom;
}Player;

void createPlayer(Player* p,char *name,Room* r);

void playerInfo(Player *player);

void pickup(Player* p,Item *item);

void inventory(Player* p);

void move(Player* p,char* direction);

void attack(Player *player, Creature *creature); 

void controlAttack(Player* player);

void controlItem(Player *player) ;

void controlMove(Player* player) ;



#endif
