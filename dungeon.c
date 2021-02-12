#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeon.h"

int main(){
  // arrays are row major
  struct node table[DUNGEONY][DUNGEONX];
  for (int i = 0; i < DUNGEONY; i++) {
    for (int j = 0; j < DUNGEONX; j++) {
      table[i][j].status = ROCK;
    }
  }
  srand(time(NULL));
  // TODO: determine optimal value for numRooms
  // for now, we'll keep this at the minimum of 6
  int numRooms = 6;
  struct room rooms[numRooms];
  
  // add rooms to the dungeon
  initDungeon(rooms, numRooms);
  
  // initialize the table to represent the dungeon rooms
  initTable(table, rooms, numRooms);
  
  initCorridor(table, rooms, numRooms);
  
  // place one upward staircase and up to 3 downward staircases
  placeStairs(table, 3);
  
  printTable(table);
}

// initializes a dungeon with a set number of rooms
void initDungeon(struct room *rooms, int numRooms) {
  int pass = 0; // sentinel value for if the dungeon is valid
  
  // loops until a valid combination is found
  while(!pass) {
    pass = 1;
  
    for(int i = 0; i < numRooms; i++) {
      // rooms cannot occupy the perimeter of the dungeon
      rooms[i].locationY = rand()%(DUNGEONY - 2) + 1;
      // e.g. DUNGEONX = 80, indexes 0 -> 79, cannot use 0 or 79 as locations
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
}

// initializes the table based on the location of rooms
void initTable(struct node table[DUNGEONY][DUNGEONX], struct room *rooms, int numRooms) {
  for(int i = 0; i < numRooms; i++){
    // this should assign floor values to the table
    for (int j = rooms[i].locationY; j < rooms[i].locationY + rooms[i].sizeY; j++) {
      for (int k = rooms[i].locationX; k < rooms[i].locationX + rooms[i].sizeX; k++) {
        table[j][k].status = ROOM;
      }
    }
  }
}

// calls an additional function to place an upward stair and a number of downward stairs
// maxStairs represents the maximum possible number of downward stairs (can be fewer than maxStairs)
void placeStairs(struct node table[DUNGEONY][DUNGEONX], int maxStairs) {
  // calculate the number of places a stair could be located
  int freeSpace = 0;
  for (int i = 0; i < DUNGEONY; i++) {
    for (int j = 0; j < DUNGEONX; j++) {
      if (table[i][j].status) {
        freeSpace++;
      }
    }
  }
  
  // first place an upward staircase
  putStair(table, UP, freeSpace);
  
  // next place a number of downward staircases between 1 and maxStairs (inclusive)
  for(int stairCount = rand()%maxStairs + 1; stairCount > 0; stairCount--) {
    freeSpace--; // decrement freeSpace every time a stair is placed
    putStair(table, DOWN, freeSpace);
  }
}

// function that actually places the stair on the table (3 for up, 4 for down)
void putStair(struct node table[DUNGEONY][DUNGEONX], int direction, int freeSpace) {
  int stairLoc = rand()%freeSpace + 1;
  
  int currLoc = 0;
  
  for (int i = 0; i < DUNGEONY; i++) {
    for (int j = 0; j < DUNGEONX; j++) {
      // only valid stair locations are floors (room and corridor)
      if (table[i][j].status == 1 || table[i][j].status == 2) {
        currLoc++;
        if (currLoc == stairLoc) {
          table[i][j].status = direction;
        }
      }
    }
  }
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
// rock = 0; room floor = 1; corridor floor = 2, up stair = 3, down stair = 4
void printTable(struct node table[DUNGEONY][DUNGEONX]) {
  for (int i = 0; i < DUNGEONY; i++) {
    for (int j = 0; j < DUNGEONX; j++) {
      if (table[i][j].status == 0) {
        printf(" ");
      }
      else if (table[i][j].status == 1) {
        printf(".");
      }
      else if (table[i][j].status == 2) {
        printf("#");
      }
      else if (table[i][j].status == 3) {
        printf("<");
      }
      else if (table[i][j].status == 4) {
        printf(">");
      }
      else {
        printf("?");
      }
    }
    printf("\n");
  }
}

// makes a path between corners of the rooms; column then row
void initCorridor(struct node table[DUNGEONY][DUNGEONX], struct room *rooms, int numRooms){
  int x;
  int y;
  for(int i = 1; i < numRooms; i++){
    x = rooms[i].locationX - rooms[i-1].locationX;
    y = rooms[i].locationY - rooms[i-1].locationY;
    int j = 0;
    while (j != x) {
      if(table[rooms[i - 1].locationY][rooms[i - 1].locationX + j].status != ROOM){
	table[rooms[i - 1].locationY][rooms[i - 1].locationX + j].status = CORR;
      }
      if (x > 0) {
        j++;
      }
      else {
        j--;
      }
    }
    int k = 0;
    while (k != y) {
      if(table[rooms[i - 1].locationY + k][rooms[i - 1].locationX + j].status != ROOM){
	table[rooms[i - 1].locationY + k][rooms[i - 1].locationX + j].status = CORR;
      }
      if (y > 0) {
        k++;
      }
      else {
        k--;
      }
    }
  }
  
}

/*
void initCorridor(struct node table[DUNGEONY][DUNGEONX], struct room *rooms, int numRooms){
  // no node is visited in the beginning
  int visited[DUNGEONY][DUNGEONX];
  for (int i = 0; i < DUNGEONY; i++) {
    for (int j = 0; j < DUNGEONX; j++) {
      visited[i][j] = 0;
    }
  }
  
  int y = rooms[0].locationY;
  int x = rooms[0].locationX;
  
  for (int count = 0; count < DUNGEONY * DUNGEONX; count++) {
    visited[y][x] = 1;
    
  }
  
  struct node currNode = table[rooms[1].locationY][rooms[1].locationX];
  while (currNode != table[rooms[0].locationY][rooms[0].locationX]) {
    // check if node is rock, turn to corridor
    if (currNode.status == ROCK) {
      currNode.status = CORR;
    }
    // go to previous node
    currNode = currNode.prev;
  }
}

int getHardness(struct node node) {
  if (node.status == ROCK) {
    return 5;
  }
  else if (node.status == ROOM) {
    return 1;
  }
  else if (node.status == CORR) {
    return 1;
  }
  else {
    return 1000;
  }
}
*/
