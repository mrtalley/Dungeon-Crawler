#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdio.h>
#include <stdlib.h>

#include "endian.h"
#include "heap.h"

#define MAXROOMS 10
#define COLS 80
#define ROWS 21
#define MAX_MONSTERS 20
#define MIN_MONSTERS 10

#define PC 2222

#define mapxy(x, y) (d->map[y][x])
#define hardnessxy(x, y) (d->hardness[y][x])

typedef enum dim {
    dim_x,
    dim_y,
    num_dims
} dim_t;

typedef int16_t pair_t[num_dims];

typedef struct pc {
    pair_t position;
    uint8_t speed;
    uint16_t type;
    uint8_t alive;
    pair_t prevPos;
    uint8_t queueNum;
    uint8_t lineOfSight;
    pair_t lastPCPos;
} pc_t;

typedef struct monster {
    uint16_t code;
    pair_t position;
    uint8_t queueNum;
    uint8_t lineOfSight;
    uint8_t speed;
} monster_t;

typedef struct dungeon {
    uint32_t num_rooms;
    uint8_t hardness[ROWS][COLS];
    char map[ROWS][COLS];
    uint8_t rooms[MAXROOMS][4]; // y, x, y-size, x-size
    uint32_t version;
    uint8_t distance_to_pc[ROWS][COLS];
    uint8_t tunnel_to_pc[ROWS][COLS];
    pc_t pc;
    // monster_t monsters[MAX_MONSTERS];
    uint32_t num_monsters;
    pc_t npc[ROWS][COLS];
    uint32_t gameTime;
} dungeon_t;

int generateRandom(int max, int min);
void setRoomsFromFile(dungeon_t *d);
void setMapFromFile(dungeon_t *d);
void writeToFile(dungeon_t *dungeon, char *filePath);
void loadFromFile(dungeon_t *dungeon, char *filePath);

#endif
