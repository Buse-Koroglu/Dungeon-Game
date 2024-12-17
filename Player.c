#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Player.h"
#include "Room.h"
#include "Creature.h"
#include "Item.h"

// createPlayer ile kullanıcıdan sadece isim ve oyuna başlayacağı odayı parametre olarak yazdım.
// sağlık, güç ve inventory'i default değerlerle başlattım.
void createPlayer(Player* p,char* name,Room* firstRoom){  
 p->name=strdup(name);
 p->health=100;
 p->strength=10;
 p->inventoryA =(Item **)malloc(sizeof(Item *) * INVENTORY_CAPACITY);
 p->inventoryCount=0;
 p->currentRoom = firstRoom;
 printf("NEW PLAYER CREATED => ");
 printf("Name : %s\n",p->name);
 printf("-----------------------------------------------------\n");
}

// oyuncu bilgilerini görmek için
void playerInfo(Player* p){
    printf("Name : %s\n",p->name);
    printf("Health : %d\n",p->health);
    printf("Strength : %d\n",p->strength);
    printf("-----------------------------------------------------\n");
}

// move methodu ile kullanıcıdan alınan yön girdisine göre bir sonraki odamızın bağlantısını kontrol edip player'ın currentRoom'unu güncellemiş oluyoruz.
void move(Player* player, char *direction) {
    Room *currentRoom = player->currentRoom;
    Room *nextRoom = NULL;

    if (strcmp(direction, "up") == 0) {
        nextRoom = currentRoom->connections[UP];
    } else if (strcmp(direction, "down") == 0) {
        nextRoom = currentRoom->connections[DOWN];
    } else if (strcmp(direction, "left") == 0) {
        nextRoom = currentRoom->connections[LEFT];
    } else if (strcmp(direction, "right") == 0) {
        nextRoom = currentRoom->connections[RIGHT];
    }

    if (nextRoom != NULL) {
        printf("Moving to the %s\n", direction);
        player->currentRoom = nextRoom;  
        printf("You arrived at : Room %d\n", nextRoom->id);
    } else {
        printf("You can not move in that direction! No connection exists.\n");
    }
    printf("-----------------------------------------------------\n");
}


// pickup methodu ile oyuncu ve item parametrelerini alarak toplamak istediğimiz eşyaları inventoryA'ya ekliyorum.
// Aldıktan sonra eğer aldığım eşyanın türü potion ise oyuncu sağlığına potion'ın iyileştirme değerini ekliyorum.
// Eğer alınan eşya silah ise oyuncunun artık gücü aldığı silahın saldırı gücüne eşitleniyor.
void pickup(Player* p,Item* item){
 if(p->inventoryCount<INVENTORY_CAPACITY){
    p->inventoryA[p->inventoryCount]=item;
    p->inventoryCount++;
    printf("You picked up %s\n",item->name);
    if(item->type==ITEM_TYPE_POTION){
        p->health+=item->value;
    printf("Your health increase %d\n",item->value);    
    }
    else if(item->type==ITEM_TYPE_WEAPON){
        p->strength=item->value;
    printf("Your strength is %d with %s\n",item->value,item->name);    
    }
 }
 else {
    printf("Inventory full! You can not add %s.\n",item->name);
    }
  printf("-----------------------------------------------------\n");
}

// inventory methodu ile oyun içinde oyuncunun topladığı tüm eşyaları görüntüleyebiliyorum.
void inventory(Player* p){
    printf("INVENTORY => ");
    for(int i=0; i < p->inventoryCount ;i++){
   printf("%d. %s  ", i + 1, p->inventoryA[i]->name);   
    }   
    printf("\n");
    
    printf("-----------------------------------------------------\n");
}


// attack methodu ile odalar içinde karşılaştığımız yaratıklarla savaşırız.Hem oyuncu hem yaratık aynı anda birbirleriyle savaşıp karşı tarafın sağlığını 0'a indirmeye çalışır.
void attack(Player *player, Creature *creature) {
        printf("%s HEALTH : %d\n",player->name,player->health);
        printf("%s HEALTH : %d\n",creature->name,creature->health);
        printf("%s attacks %s for %d damage!\n", player->name, creature->name, player->strength);
        printf("%s attacks %s for %d damage!\n", creature->name, player->name, creature->strength);
    while (creature->health > 0 && creature->health > 0) {
        creature->health -= player->strength;
         player->health -=  creature->strength; 
         }    

    if (player->health <= 0) {
            player->health = 0;
            printf("%s, you died!\n", player->name);
            exit(EXIT_SUCCESS);  // Oyunu bitir
    }  
    else if (creature->health <= 0) {
        creature->health=0;
        printf("%s HEALTH : %d\n", player->name, player->health);
        printf("%s HEALTH : %d\n", creature->name, 0);
        printf("%s has been defeated!\n", creature->name);
        if (player->currentRoom->id == 6) {
                printf("You have defeated the BOSS at the end of the dungeon!! YOU WIN!!\n");
                exit(EXIT_SUCCESS);  // Oyunu bitir
            }
        return;
    }
        printf("-----------------------------------------------------\n");
    } 

// controlAttack methodum aslında attack fonksiyonunu kullanmak için yardımcı bir fonksiyon.Bu fonksiyonda savaşmadan önce odada creature olup olmadığını kontrol ediyorum. 
void controlAttack(Player* player){
    if (player->currentRoom->creature == NULL) {
        printf("No creature to fight in this room.\n");
        return;
    }
     if(player->currentRoom->creature!=NULL){
      printf("There is %s in this room , you have to fight with creature!!!\n",player->currentRoom->creature->name);
      attack(player,player->currentRoom->creature);      
    }
     printf("-----------------------------------------------------\n");
}

// controlItem methodum da aynı şekilde pickup fonksiyonunu kullanabilmem için bir yardımcı fonksiyon görevi görür. Bu fonksiyonda odada item olup olmadığı kontrol edilir.
// Eğer item varsa oyuncunun item'i alıp almak istemediği sorulur.
void controlItem(Player *player) {
    // Oda içinde item var mı kontrol et
    if (player->currentRoom->items != NULL) {
        char choice[16];
        printf("There are %d item in this room. Do you want to take it? (yes/no): ",player->currentRoom->itemNumber);
        scanf("%15s", choice);
        // Eğer oyuncu 'yes' derse, itemleri al
            if (strcmp(choice, "yes") == 0) {
            for (int i = 0; i < player->currentRoom->itemNumber; i++) {
                // Oda içindeki item'ları tek tek al
                pickup(player, player->currentRoom->items[i]); // Item'ı envantere ekle
            } }else {
            printf("You don't want to choose take any items.\n");
        }
    } else {
        printf("There are no items in this room.\n");
    } 
     printf("-----------------------------------------------------\n");
} 

// controlMove fonksiyonumu move fonksiyonunu daha rahat kontrol edebilmek için yazdım.
// Bu fonksiyonla birlikte kullanıcıdan hangi yöne gitmek istediğini eğer orada bir oda yoksa tekrar sorulmasını sağladı.
void controlMove(Player* player) {
    char direction[16]; // Kullanıcıdan yön almak için
    while (1) {
        printf("Which direction do you want to move? (up/down/left/right): ");
        scanf("%15s", direction);
        Room *currentRoom = player->currentRoom;
        int canMove = 0;
        // Bağlantılı olduğu odaların kontrolü
        if (strcmp(direction, "up") == 0 && currentRoom->connections[UP] != NULL) {
            canMove = 1;
        } else if (strcmp(direction, "down") == 0 && currentRoom->connections[DOWN] != NULL) {
            canMove = 1;
        } else if (strcmp(direction, "left") == 0 && currentRoom->connections[LEFT] != NULL) {
            canMove = 1;
        } else if (strcmp(direction, "right") == 0 && currentRoom->connections[RIGHT] != NULL) {
            canMove = 1;
        }

        // Geçerli bir yön girildiyse ve o yönde geçerli bir oda varsa hareket eder ve döngüden çıkar.
        if (canMove) {
            move(player, direction);
            break;
        } else {
            printf("Invalid direction or no connection in that direction. Please enter a valid direction.\n");
        }
    }
     printf("-----------------------------------------------------\n");
}