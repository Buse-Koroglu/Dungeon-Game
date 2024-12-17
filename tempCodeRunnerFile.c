
#include <stdio.h>
#include <stdlib.h>

#include "Player.h"
#include "Room.h"
#include "Creature.h"
#include "Item.h"
#include "Player.c"
#include "Room.c"
#include "Creature.c"
#include "Item.c"


int saveCounter=1;

void listSavedGames() {
    char filename[20];
    FILE* file;
    int saveIndex = 1; // Kaydedilen oyunların numarası
    printf("Saved Game Files:\n");
    while (1) {
        snprintf(filename, sizeof(filename), "save%d.txt", saveIndex);
        file = fopen(filename, "r");
        if (file == NULL) {
            // Dosya bulunamazsa döngüden çık
            break;
        }
        printf("File: %s\n", filename);
        printf("  Content:\n");
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("    %s", line);
        }
        fclose(file);
        printf("\n");
        saveIndex++; // Bir sonraki dosyayı kontrol edebilmek için
    }

    if (saveIndex == 1) {
        printf("There is no saved games.\n");
    }
}

void save(Player *player, int currentRoomNumber) {
    FILE *file = fopen("save1.txt", "w");
      if (file == NULL) {
        fprintf(stderr, "Error: Can not open file '%s'.\n", file);
        exit(EXIT_FAILURE); 
    }
    fprintf(file, "PlayerName: %s\n", player->name);
    fprintf(file, "CurrentRoom: %d\n", currentRoomNumber);

    fprintf(file, "Inventory: ");
    for (int i = 0; i < player->inventoryCount; i++) {
        fprintf(file, "%d ", player->inventoryA[i]->type);
    }
    fprintf(file, "\n");

    fclose(file);
    printf("Game successfully saved!\n");
}

void load(Player* player, const char* filename, Room* rooms, int roomCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can not open file '%s'.\n", file);
        exit(EXIT_FAILURE); 
    }
    char playerName[15];
    int currentRoomNumber;
    int playerHealth;
    int inventory[10]; // Maksimum 10 item için
    int inventoryCount = 0;

    // oyuncu özelliklerini çekmek için
    fscanf(file, "PlayerName: %s\n", playerName);
    fscanf(file, "CurrentRoom: %d\n", &currentRoomNumber);
    fscanf(file, "Health: %d\n", &playerHealth);

    // for inventory 
    char inventoryLine[256];
    if (fgets(inventoryLine, sizeof(inventoryLine), file) != NULL) {
        if (strncmp(inventoryLine, "Inventory:", 10) == 0) {
            char* token = strtok(inventoryLine + 10, " ");
            while (token != NULL) {
                inventory[inventoryCount++] = atoi(token);
                token = strtok(NULL, " ");
            }
        }
    }
    fclose(file);
    createPlayer(player, playerName, &rooms[currentRoomNumber - 1]); // 
    player->health = playerHealth;

    printf("Previous game successfully loaded! Player '%s' starting in Room %d with health %d.\n", playerName, currentRoomNumber, playerHealth);
}


int main() {

    Player player;

    int roomCount = 6;
    int creatureCount = 4;
    int itemCount = 6;

    // Room Creature ve Item dinamik olarak tuttum.
    Room* rooms = malloc(roomCount * sizeof(Room));
    Creature* creatures = malloc(creatureCount * sizeof(Creature));
    Item* items = malloc(itemCount * sizeof(Item));

    loadCreatureStats("creaturestats.txt",creatures,&creatureCount); // txt dosyasından yaratık bilgilerini yükledim.

    // itemleri türlerine göre başlattım.
    initializeItem(&items[0],ITEM_TYPE_POTION);
    initializeItem(&items[1],ITEM_TYPE_WEAPON);
    initializeItem(&items[2],ITEM_TYPE_KEY);
    initializeItem(&items[3],ITEM_TYPE_POTION);
    initializeItem(&items[4],ITEM_TYPE_WEAPON);
    initializeItem(&items[5],ITEM_TYPE_WEAPON);

    loadItemAttributes("itemattributes.txt", items, &itemCount);  // txt dosyasından item özelliklerini ekledim.


    // Odaları başlatıp , numaralandırma işlemi yaptım.
    for(int i=0;i<roomCount;i++){
     initializeRoom(&rooms[i],i+1);
    }

    // odaların karşılıklı bağlantılarını kurdum.
    connectRooms(&rooms[0], &rooms[1], RIGHT);
    connectRooms(&rooms[0], &rooms[3], DOWN);
    connectRooms(&rooms[1], &rooms[2], RIGHT);
    connectRooms(&rooms[1], &rooms[4], DOWN);
    connectRooms(&rooms[2], &rooms[5], DOWN);
    connectRooms(&rooms[3], &rooms[4], RIGHT);
    connectRooms(&rooms[4], &rooms[5], RIGHT);

    addItemToRoom(&rooms[1],&items[0]);
    addItemToRoom(&rooms[2],&items[1]); // Hem weapon hem key itemi bulunacak.
    addItemToRoom(&rooms[2],&items[2]);
    addItemToRoom(&rooms[3],&items[3]); // Hem weapon hem potion itemi bulunacak.
    addItemToRoom(&rooms[3],&items[4]);
    addItemToRoom(&rooms[4],&items[5]);

    addCreatureToRoom(&rooms[0],&creatures[0]); // İLK ODADA GARDİYAN OLACAK.
    addCreatureToRoom(&rooms[1],&creatures[1]); // İKİNCİ ODADA BİR TANE BİG BUG OLACAK.
    // 3. VE 4.ODALARDAN TEÇHİZAT ALINABİLECEK , O YÜZDEN YARATIK YOK.
    addCreatureToRoom(&rooms[2],NULL);
    addCreatureToRoom(&rooms[3],NULL);
    addCreatureToRoom(&rooms[4],&creatures[2]); // 5.ODADA ZOMBİ OLACAK.
    addCreatureToRoom(&rooms[5],&creatures[3]); // SON ODADA BOSS YANİ BÖLÜM SONU CANAVARI İLE SAVAŞACAK.


    loadRoomDescriptions("roomdescriptions.txt", rooms, roomCount); // txt dosyasından oda açıklamalarını ekledim.


    printf("WELCOME TO THE ADVENTURE GAME\n");

    // HARITA BASLANGIÇ
    FILE *dosya; 
    char satir[256]; 
    dosya = fopen("map.txt", "r"); 
    if (dosya == NULL) { 
        printf("Can not open this file.\n");
        return 1;
    }
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        printf("%s", satir); 
    }
    fclose(dosya); 
    // HARITA BITIŞ
    

    int option1;
    printf("WELCOME TO THE ADVENTURE GAME\n");
    printf("1. Start a New Game\n");
    printf("2. Load a Saved Game\n");
    printf("Choose an option: ");
    scanf("%d", &option1);

    if (option1 == 2) {
        load(&player, "save1.txt", rooms, roomCount); // load -> önceden kaydedilen oyuna kaldığı yerden devam etmesini sağlar.
    }else {     
        char name[15];    // burada ise yeni bir oyun başlatılır.                            
        printf("Hello Player! What is your name? "); 
        scanf("%14s", name);
        createPlayer(&player, name, &rooms[0]);
    }

    int option2 ;
    printf("GAME MENU\n"); 
    printf("1.Save Game\n");
    printf("2.Load Game\n");
    printf("3.List Saved Games\n");
    printf("4.Player Information\n");
    printf("5.Look\n");
    printf("6.Move\n");
    printf("7.Pickup\n");
    printf("8.Inventory\n");
    printf("9.Attack\n");
    printf("10.Exit\n");
   
    while(1){
    printf("Choose one option please(1-2-3-4-5-6-7-8-9-10): ");
    scanf("%d",&option2);
    if(option2==1){
        save(&player, player.currentRoom->id);
    }
    if(option2==2){
        load(&player, "save1.txt", rooms, roomCount);
    }
    if(option2==3){
        listSavedGames();
    }
    if(option2==4){
       playerInfo(&player); 
    }
    if(option2==5){
       look(player.currentRoom);
    }
    if(option2==6){
       controlMove(&player);
    }
    if(option2==7){
       controlItem(&player);
    }
    if(option2==8){
       inventory(&player);
    }
    if(option2==9){
       controlAttack(&player);
    }
    if(option2==10){
      exit(EXIT_SUCCESS);
    }
   }

    // Room Creature ve Item tuttuğum bellek alanını clean fonksiyonları ile serbest bırakıyorum.
    cleanupRooms(rooms, roomCount);
    cleanupCreatures(creatures, creatureCount);
    cleanupItems(items,itemCount);


  
    return 0;


}
