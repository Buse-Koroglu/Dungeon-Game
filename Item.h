#ifndef ITEM_H
#define ITEM_H


typedef enum {
    ITEM_TYPE_WEAPON,
    ITEM_TYPE_POTION,
    ITEM_TYPE_KEY,
    } ItemType;

// Item yapısı
typedef struct Item {
    char *name;
    ItemType type;  
    int value;  // verdiği güç ya da iyileşme değeri 

} Item;

void loadItemAttributes(const char *filename, Item *items, int *itemCount) ;

void initializeItem(Item *item,ItemType type);

void itemInfo( Item *item);

void cleanupItems(Item* items, int itemCount); 

#endif
