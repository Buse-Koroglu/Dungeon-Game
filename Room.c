#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Room.h"
#include "Player.h"
#include "Item.h"
#include "Creature.h"


void loadRoomDescriptions(const char *filename, Room *rooms, int roomCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    char line[256]; // Her satır için buffer
    while (fgets(line, sizeof(line), file)) {
        int roomId;
        char description[256];

        // Satırı ayrıştır: "ID: Description"
        if (sscanf(line, "%d: %[^\n]", &roomId, description) == 2) {
            if (roomId > 0 && roomId <= roomCount) {
                rooms[roomId - 1].description = strdup(description); // Açıklamayı kaydet
            }
        }
    }

    fclose(file);
}

// look methodu ile oyuncunun anlık olarak bulunduğu odayı , oda numarasını ve oda açıklamasını görebiliriz.
// aynı zamanda odada bulunan itemleri ve yaratık bilgisini de yazdırır.
void look(Room* r) {
    printf("You are in Room %d :%s \n",r->id,r->description);
    printf("There are %d items in this room!!!\n", r->itemNumber);
    printf("ITEMS: ");
    for (int i = 0; i < r->itemNumber; i++) {
        printf("%s", r->items[i]->name); 
        if (i < r->itemNumber - 1) {
            printf(", ");
        }
    }
    if (r->itemNumber == 0) {
        printf("-");
    }
    printf("\n");
    printf("CREATURE: ");
if (r->creature != NULL) { 
    printf("%s (Health: %d)\n", r->creature->name, r->creature->health);
} else {
    printf("There are no creatures in Room %d!!!\n", r->id);
}
printf("-----------------------------------------------------\n");
}


// Oda oluşturma fonksiyonu
void initializeRoom(Room *room, int id) {
    room->id = id;
    room->items = (Item **)malloc(sizeof(Item *) * 10); // bir odanın içerebilceği maximum item sayısı 10'dur.
    room->itemNumber = 0;
    for (int i = 0; i < 4; i++) { // default olarak başlangıçta tüm odaların connection'ları NULL
        room->connections[i] = NULL;
    }
    room->creature = (Creature*)malloc(sizeof(Creature)); // Odada bulunabilecek bir Creature nesnesi için bellek ayırdım.
    room->creatureCount = 0;
}

// Odaya item  ekleme fonksiyonu
void addItemToRoom(Room *room, Item *item) {
    room->items[room->itemNumber] = item;
    room->itemNumber++;
}

void addCreatureToRoom(Room *room,Creature *creature){
    if(room->creatureCount==0){
        room->creature=creature;
        room->creatureCount++;
    }
}

// odalar arasındaki bağlantıyı kurduğum fonksiyon
void connectRooms(Room *room, Room *connectedRoom, Direction direction) {
    room->connections[direction] = connectedRoom;

    Direction opposite;
    if (direction == UP) {
        opposite = DOWN;
    } else if (direction == DOWN) {
        opposite = UP;
    } else if (direction == LEFT) {
        opposite = RIGHT;
    } else if (direction == RIGHT) {
        opposite = LEFT;
    }
    // Odaları karşılıklı olarak bağladım.
    connectedRoom->connections[opposite] = room;
}

void cleanupRooms(Room* rooms, int roomCount) {
    free(rooms); // Tüm oda dizisini serbest bıraktım.
}