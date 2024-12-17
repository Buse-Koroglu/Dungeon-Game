#include "Creature.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void loadCreatureStats(const char *filename, Creature *creatures, int *creatureCount) {
      FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    char line[256]; 
    *creatureCount = 0;

    while (fgets(line, sizeof(line), file)) {
        char creatureName[128];
        int health, strength;
        if (sscanf(line, "%[^,],%d,%d", creatureName, &health, &strength) == 3) {
            creatures[*creatureCount].name = strdup(creatureName);  // Creature adı
            creatures[*creatureCount].health = health;              // Health değeri
            creatures[*creatureCount].strength = strength;          // Strength değeri
            (*creatureCount)++;
        } else {
            fprintf(stderr, "Malformed line: %s\n", line);
        }
    }

    fclose(file);
}

void creatureInfo(Creature *creature) {
    printf("Creature : %s\n" , creature->name);
    printf("Health : %d\n" , creature->health);
    printf("Strength : %d\n", creature->strength);
}

void cleanupCreatures(Creature* creatures, int creatureCount) {
    for (int i = 0; i < creatureCount; i++) {
        free(creatures[i].name); // Yaratıkların ismi için ayrılan belleği serbest bıraktım.
    }
    free(creatures); // Tüm yaratık dizisini serbest bıraktım.
}