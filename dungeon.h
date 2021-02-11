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
void printTable(int table[21][80]);
