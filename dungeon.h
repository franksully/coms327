#define DUNGEONX 80
#define DUNGEONY 21
#define MINROOMX 4
#define MINROOMY 3
#define MAXROOMX 12
#define MAXROOMY 9

#define ROCK 0
#define ROOM 1
#define CORR 2
#define UP 3
#define DOWN 4

struct room {
  int locationX;
  int locationY;
  int sizeX;
  int sizeY;
};

struct node {
  int status;
  int dist;
  //struct node prev;
};

void initDungeon(struct room *rooms, int numRooms);
void initTable(struct node table[DUNGEONY][DUNGEONX], struct room *rooms, int numRooms);
void placeStairs(struct node table[DUNGEONY][DUNGEONX], int maxStairs);
void putStair(struct node table[DUNGEONY][DUNGEONX], int direction, int freeSpace);
int twoRoomsCollide(int l1x, int l1y, int r1x, int r1y, int l2x, int l2y, int r2x, int r2y);
void printTable(struct node table[DUNGEONY][DUNGEONX]);
void initCorridor(struct node table[DUNGEONY][DUNGEONX], struct room *rooms, int numRooms);
int getHardness(struct node node);

