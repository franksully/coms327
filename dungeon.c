#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeon.h"


#define DUNGEONX 80
#define DUNGEONY 21
#define MINROOMX 4
#define MINROOMY 3
#define MAXROOMX 12
#define MAXROOMY 9

struct room {
  int locationX;
  int locationY;
  int sizeX;
  int sizeY;
};

struct stone{
  int locationX;
  int locationY;
  int hardness;
};


int main(){
  // arrays are row major
  int table[DUNGEONY][DUNGEONX];
  srand(time(NULL));
  // TODO: determine optimal value for numRooms
  // for now, we'll keep this at the minimum of 6
  int numRooms = 6;
  struct room rooms[numRooms];
  int i;
  for(i = 0; i < numRooms; i++){
    // rooms cannot occupy the perimeter of the dungeon
    // TODO: validate these values
    rooms[i].locationY = rand()%(DUNGEONY - 2) + 1;
    rooms[i].locationX = rand()%(DUNGEONX - 2) + 1;
    
    // max sizeY value is 11
    rooms[i].sizeY = rand()%MAXROOMY + MINROOMY;
    // max sizeX value is 15
    rooms[i].sizeX = rand()%MAXROOMX + MINROOMX;
    
    // this should assign floor values to the table
    for (int j = rooms[i].locationY; j < rooms[i].locationY + rooms[i].sizeY; j++) {
      for (int k = rooms[i].locationX; k < rooms[i].locationX + rooms[i].sizeX; k++) {
        table[j][k] = 1;
      }
    }
  }
  
  printTable(table);
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

