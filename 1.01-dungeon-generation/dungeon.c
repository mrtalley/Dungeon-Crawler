#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <curses.h>

#define MAXROOMS 10
#define COLS 80
#define ROWS 21

struct Dungeon {
  unsigned char hardness[COLS][ROWS];
  char map[COLS][ROWS];
  unsigned char rooms[MAXROOMS][2];
} dungeon;

static void createEmptyMap(struct Dungeon *dungeon);
static void generateRooms(struct Dungeon *dungeon);
static void printMap(struct Dungeon *dungeon);
int generateRandom(int max, int min);
int roomCheck(int yPos, int xPos, int ySize, int xSize, struct Dungeon *dungeon);
static void generateCorridors(struct Dungeon *dungeon);

int main(int argc, char* argv[]) {
  struct Dungeon dungeon;
  createEmptyMap(&dungeon);
  generateRooms(&dungeon);
  generateCorridors(&dungeon);
  printMap(&dungeon);
}

static void createEmptyMap(struct Dungeon *dungeon) {
  srand((unsigned) time(NULL));
  int y = 0, x = 0;
  for(y = 0; y < ROWS; y++) {
    for(x = 0; x < COLS; x++) {
      if(x == 0 || x == 79) {
        dungeon->map[x][y] = '|';
        dungeon->hardness[x][y] = 255;
      }
      else if(y == 0 || y == 20) {
        dungeon->map[x][y] = '-';
        dungeon->hardness[x][y] = 255;
      }
      else {
        dungeon->map[x][y] = ' ';
        dungeon->hardness[x][y] = generateRandom(254, 1);
      }
    }
  }
}

static void generateRooms(struct Dungeon *dungeon) {
  srand((unsigned) time(NULL));
  int i = 0, j = 0;
  int max = 10, min = 5;
  int maxRooms = generateRandom(max, min);
  int numRooms = 0;
  int xMin = 3, yMin = 5, xMax = 10, yMax = 15;
  int x = 0, y = 0, xSize = 0, ySize = 0;
  int success = 1;
  int tries = 0;
  int roomPosition = 0;

  while(numRooms != maxRooms) {
    x = generateRandom(COLS - 1, 1);
    y = generateRandom(ROWS - 1, 1);
    xSize = generateRandom(xMax, xMin);
    ySize = generateRandom(yMax, yMin);

    if(!(x + xSize < COLS && y + ySize < ROWS)) {
      success = 0;
    }

    if(!(roomCheck(x, y, xSize, ySize, dungeon)) && success) {
      success = 0;
    }

    if(success) {
      for(j = y; j < y + ySize; j++) {
        for(i = x; i < x + xSize; i++) {
          dungeon->map[i][j] = '.';
          dungeon->hardness[i][j] = 0;
        }
      }

      dungeon->rooms[numRooms][roomPosition] = x + (xSize / 2);
      roomPosition++;
      dungeon->rooms[numRooms][roomPosition] = y + (ySize / 2);
      numRooms++;
      roomPosition = 0;
    }
    success = 1;
    tries++;
  }

  printf("Rooms generated in %d tries\n", tries);
}

static void printMap(struct Dungeon *dungeon) {
  int y = 0, x = 0;
  for(y = 0; y < ROWS; y++) {
    for(x = 0; x < COLS; x++) {
      printf("%c", dungeon->map[x][y]);
    }
    printf("\n");
  }
}

int generateRandom(int max, int min) {
  return (rand() % (max - min)) + min;
}

int roomCheck(int xPos, int yPos, int xSize, int ySize, struct Dungeon *dungeon){
  int y, x;
  for(y = yPos; y < yPos + ySize; y++) {
    if(dungeon->hardness[xPos - 1][y] == 0
      || dungeon->hardness[xPos + xSize][y] == 0)
      {
        return 0;
      }
  }

  for(x = xPos; x < xPos + xSize; x++) {
    if(dungeon->hardness[x][yPos - 1] == 0
      || dungeon->hardness[x][yPos + ySize] == 0)
      {
        return 0;
      }
  }

  return 1;
}

static void generateCorridors(struct Dungeon *dungeon) {

}