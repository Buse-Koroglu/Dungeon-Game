#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void loadItemAttributes(const char *filename, Item *items, int *itemCount) { // txt dosyasından item özelliklerini eklemek için kullandım.
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    char line[256]; 
    *itemCount = 0;
    while (fgets(line, sizeof(line), file)) {
        char itemName[128];
        int itemValue;
        if (sscanf(line, "%[^,],%d", itemName, &itemValue) == 2) {
            items[*itemCount].name = strdup(itemName);  
            items[*itemCount].value = itemValue;       
            (*itemCount)++;
        } else {
            fprintf(stderr, "Malformed line: %s\n", line);
        }
    }

    fclose(file);
}


void initializeItem(Item *item,ItemType type) {
        item->type = type;
}

void itemInfo(Item *item) {
    printf("Item: %s\n", item->name);
    printf("Type: ");
    switch (item->type) {
        case ITEM_TYPE_WEAPON:
            printf("Weapon\n");
            break;
        case ITEM_TYPE_POTION:
            printf("Potion\n");
            break;
        case ITEM_TYPE_KEY:
            printf("Key\n");
            break;
    }
    printf("Value: %d\n", item->value);
}


void cleanupItems(Item* items, int itemCount) {
    for (int i = 0; i < itemCount; i++) {
        free(items[i].name); // Item adı için ayrılan belleği serbest bıraktım.
    }
    free(items); // Tüm item dizisini serbest bıraktım.
}