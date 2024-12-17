#ifndef ROOM_H
#define ROOM_H 
#include "Player.h"
#include "Item.h"
#include "Creature.h"


typedef enum {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct Room {
    int id;
    char *description;
    Item **items;
    int itemNumber;
    struct Room *connections[4];  // sağ , sol , yukarı , aşağı
    struct Creature* creature;
    int creatureCount;
} Room;

void loadRoomDescriptions(const char *filename, Room *rooms, int roomCount) ;
void look(Room* r);
void initializeRoom(Room *room,int id);
void addItemToRoom(Room *room, Item *item);
void addCreatureToRoom(Room *room, Creature *creature);
void connectRooms(Room* r1,Room* r2,Direction d);
void cleanupRooms(Room* rooms, int roomCount) ;


#endif