# Dungeon-Game

Prepared by: Buse Köroğlu
Student Number: 23050111023

Overview
The Adventure Game is a text-based game where players explore different rooms, interact with creatures and items, and manage their inventory. It also features a save/load system, allowing players to save progress and continue later.

Game Flow
Initialization:
-The game starts with rooms, creatures, and items initialized.
-Rooms are interconnected, and items and creatures are placed in them.
-A map is loaded at the beginning and displayed to the player.

Starting the Game:
-Players choose to start a new game or load a saved game.
-In a new game, the player begins in the first room.
-If a saved game is loaded, the player’s state is restored, and they begin in the appropriate room.

In-Game Actions:
-Players can interact with the game menu to pick up items, fight creatures, or move between rooms.
-Players can check their inventory or save the current game state for future play.

Game Loop:
-The game interacts with the player via terminal prompts for actions.
-The loop continues until the player exits the game.

Implementation Details

1. Player
The player character is represented by the Player structure.
Attributes:
name: Player’s name
health: Player’s health status
strength: Player’s strength
inventory: Player’s collected items
currentRoom: The room the player is currently in
Functions:
controlMove: Allows the player to move between rooms.
controlItem: Enables the player to pick up items from the room.
controlAttack: Starts a battle with creatures.

2. Rooms
Rooms are represented by the Room structure, each with a number and its own set of creatures and items.
Rooms and Contents:
Room 1: Guard creature
Room 2: Big Bug creature, a healing potion
Room 3: A weapon and a key
Room 4: A weapon and an elixir
Room 5: Zombie creature, a weapon
Room 6: Boss creature
Functions:
connectRooms: Establishes connections between rooms.
look: Displays the room’s details to the player.
addItemToRoom: Adds items to rooms.
addCreatureToRoom: Adds creatures to rooms.

3. Creatures
Creatures are represented by the Creature structure.
Attributes:
name: Name of the creature
health: Creature’s health status
strength: Creature’s strength
Functions:
attack: Initiates a battle between the player and creatures.

4. Items
Items are represented by the Item structure and categorized by type.
Attributes:
type: Type of the item (e.g., weapon, potion)
value: Value of the item (e.g., attack or healing power)
Functions:
pickup: Allows the player to pick up items and add them to their inventory.

5. Save/Load System
The save/load system stores the game state in the save1.txt file or retrieves it from there.
Save: Records the player’s name, health, inventory, and current room.
Load: Restores saved game data to continue playing.
listSavedGames: Lists available saved games.
Technical Details

1. File-Based Data Storage
loadRoomDescriptions: Reads room descriptions from a file.
loadItemAttributes: Reads item types and values from a file.
loadCreatureStats: Reads creature attributes from a file.

3. Dynamic Memory Management
All rooms, creatures, and items are dynamically allocated using malloc.
At the end of the game, memory is freed using functions like cleanupRooms, cleanupCreatures, and cleanupItems to prevent leaks.

4. Error Handling
File open/read errors are handled appropriately.
Dynamic memory allocation errors are addressed.


Game Commands
-move: Moves between rooms.
-pickup & inventory: Collects items and displays inventory.
-attack: Engages in combat with creatures.
-save/load: Saves or loads the game state.
-listSavedGames: Lists all saved games.


Running the Game
Include all .c files in main.c during compilation. Run the generated main.exe file using the following command in the terminal:
.\main.exe
