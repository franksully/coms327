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
  int count = 0; // TODO: remove this, counts the number of loops

  int pass = 0; // sentinel value for if the dungeon is valid
  
  // loops until a valid combination is found
  while(!pass) {
    count++;
    pass = 1;
  
    for(int i = 0; i < numRooms; i++) {
      // rooms cannot occupy the perimeter of the dungeon
      // TODO: validate these values
      rooms[i].locationY = rand()%(DUNGEONY - 2) + 1;
      rooms[i].locationX = rand()%(DUNGEONX - 2) + 1;
      
      // max sizeY value is 11
      rooms[i].sizeY = rand()%MAXROOMY + MINROOMY;
      // max sizeX value is 15
      rooms[i].sizeX = rand()%MAXROOMX + MINROOMX;
      
      // check if the rooms exceed the bounds of the dungeon (border must be rock)
      if ((rooms[i].locationY + rooms[i].sizeY > DUNGEONY - 2) || (rooms[i].locationX + rooms[i].sizeX > DUNGEONX - 2)) {
        pass = 0;
        break;
      }
    }
    
    // now check for room overlap
    // rooms must have at least one space between them
    if (pass) { // no need to check for overlap if the rooms are out of bounds
      for(int i = 0; i < numRooms; i++) {
        for(int j = i + 1; j < numRooms; j++) {
          if (twoRoomsCollide(rooms[i].locationX, rooms[i].locationY, rooms[i].locationX + 
            rooms[i].sizeX, rooms[i].locationY + rooms[i].sizeY, rooms[j].locationX, rooms[j].locationY, 
            rooms[j].locationX + rooms[j].sizeX, rooms[j].locationY + rooms[j].sizeY)) {
	      pass = 0;
	  }
        }
      }
    }
  }
  
  printf("Number of loops before dungeon generation: %d\n\n", count);
}

// checks for overlap, returns 1 if overlap occurs
int twoRoomsCollide(int l1x, int l1y, int r1x, int r1y, int l2x, int l2y, int r2x, int r2y){
  // check if there is at least one gap between rooms
  if(l1x > r2x + 1 || l2x > r1x + 1){
    return 0;
  }
  if(l1y > r2y + 1 || l2y > r1y + 1){
    return 0;
  }
  return 1;
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

