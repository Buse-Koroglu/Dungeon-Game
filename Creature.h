#ifndef CREATURE_H
#define CREATURE_H

typedef struct Creature {
    char *name;
    int health;
    int strength;
} Creature;

void loadCreatureStats(const char *filename, Creature *creatures, int *creatureCount) ;

void creatureInfo(Creature *creature);

void cleanupCreatures(Creature* creatures, int creatureCount) ;


#endif 
