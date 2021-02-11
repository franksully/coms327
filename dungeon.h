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

void initDungeon(struct room *rooms, int numRooms);
void initTable(int table[DUNGEONY][DUNGEONX], struct room *rooms, int numRooms);
int twoRoomsCollide(int l1x, int l1y, int r1x, int r1y, int l2x, int l2y, int r2x, int r2y);
void printTable(int table[DUNGEONY][DUNGEONX]);
