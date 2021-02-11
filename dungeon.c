#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
  int table[DUNGEONX][DUNGEONY];
  srand(time(NULL));
  int numRooms = rand()%6 + 6;
  struct room rooms[numRooms];
  int i;
  for(i = 0; i < numRooms; i++){
    rooms[i].locationX = rand()%DUNGEONX + 1;
    rooms[i].locationY = rand()%DUNGEONY + 1;
    rooms[i].sizeX = rand()%MAXROOMX + MINROOMX;
    rooms[i].sizeY = rand()%MAXROOMY + MINROOMY;
  }
  
}

