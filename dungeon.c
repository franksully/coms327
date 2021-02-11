#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeon.h"

int main(){
  // arrays are row major
  int table[DUNGEONY][DUNGEONX];
  // TODO: initializes table values to 0, make this look pretty? idk
  for (int i = 0; i < DUNGEONY; i++) {
    for (int j = 0; j < DUNGEONX; j++) {
      table[i][j] = 0;
    }
  }
  srand(time(NULL));
  // TODO: determine optimal value for numRooms
  // for now, we'll keep this at the minimum of 6
  int numRooms = 6;
  struct room rooms[numRooms];
  
  initDungeon(rooms, numRooms);
  
  for(int i = 0; i < numRooms; i++){
    // this should assign floor values to the table
    for (int j = rooms[i].locationY; j < rooms[i].locationY + rooms[i].sizeY; j++) {
      for (int k = rooms[i].locationX; k < rooms[i].locationX + rooms[i].sizeX; k++) {
        table[j][k] = 1;
      }
    }
  }
  
  printTable(table);
}

// initializes a dungeon with a set number of rooms
void initDungeon(struct room *rooms, int numRooms) {
  int pass = 0; //sentinel value for if the dungeon is valid
  
  // loops until a valid combination is found
  while(!pass) {
    pass = 1;
  
    for(int i = 0; i < numRooms; i++){
      // rooms cannot occupy the perimeter of the dungeon
      // TODO: validate these values
      rooms[i].locationY = rand()%(DUNGEONY - 2) + 1;
      rooms[i].locationX = rand()%(DUNGEONX - 2) + 1;
      
      // max sizeY value is 11
      rooms[i].sizeY = rand()%MAXROOMY + MINROOMY;
      // max sizeX value is 15
      rooms[i].sizeX = rand()%MAXROOMX + MINROOMX;
      
      // TODO: remove this, for debugging purposes
      printf("Room %d: y = %d, x = %d, sizeY = %d, sizeX = %d\n", i, rooms[i].locationY, rooms[i].locationX, rooms[i].sizeY, rooms[i].sizeX);
      
      // check if the rooms exceed the bounds of the dungeon (border must be rock)
      if ((rooms[i].locationY + rooms[i].sizeY > DUNGEONY - 2) || (rooms[i].locationX + rooms[i].sizeX > DUNGEONX - 2)) {
        pass = 0;
        break;
      }
    }
  }
}

// for now, these are the values:
// rock = 0; room floor = 1; corridor floor = 2
void printTable(int table[21][80]) {
  for (int i = 0; i < DUNGEONY; i++) {
    for (int j = 0; j < DUNGEONX; j++) {
      if (table[i][j] == 0) {
        printf(" ");
      }
      else if (table[i][j] == 1) {
        printf(".");
      }
      else {
        printf("#");
      }
    }
    printf("\n");
  }
}

