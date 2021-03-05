#ifndef DUNGEON_H
#define DUNGEON_H

#include "heap.h"
#include "dims.h"

#define DUNGEON_X 80
#define DUNGEON_Y 21
#define MIN_ROOMS 6
#define MAX_ROOMS 10
#define ROOM_MIN_X 4
#define ROOM_MIN_Y 3
#define ROOM_MAX_X 20
#define ROOM_MAX_Y 15
#define SAVE_DIR ".rlg327"
#define DUNGEON_SAVE_FILE "dungeon"
#define DUNGEON_SAVE_SEMANTIC "RLG327-" TERM
#define DUNGEON_SAVE_VERSION 0U

#define mappair(pair) (d->map[pair[dim_y]][pair[dim_x]])
#define mapxy(x, y) (d->map[y][x])
#define hardnesspair(pair) (d->hardness[pair[dim_y]][pair[dim_x]])
#define hardnessxy(x, y) (d->hardness[y][x])

typedef enum __attribute__((__packed__)) terrain_type
{
  ter_debug,
  ter_wall,
  ter_wall_immutable,
  ter_floor,
  ter_floor_room,
  ter_floor_hall,
  ter_stairs,
  ter_stairs_up,
  ter_stairs_down
} terrain_type_t;

typedef struct room
{
  pair_t position;
  pair_t size;
} room_t;

typedef struct pc
{
  pair_t position;
  uint8_t speed;
  int is_alive;
  int room_num;
} pc_t;

typedef struct monster
{
  uint8_t type;
  uint8_t smart;
  uint8_t telepath;
  uint8_t tunnel;
  uint8_t erratic;
  pair_t position;
  pair_t pc_pos;
  uint8_t speed;
  int room_num;
  char symbol;
  int alive;
} monster_t;

typedef struct dungeon
{
  uint32_t num_rooms;
  room_t *rooms;
  terrain_type_t map[DUNGEON_Y][DUNGEON_X];
  /* Since hardness is usually not used, it would be expensive to pull it *
   * into cache every time we need a map cell, so we store it in a        *
   * parallel array, rather than using a structure to represent the       *
   * cells.  We may want a cell structure later, but from a performanace  *
   * perspective, it would be a bad idea to ever have the map be part of  *
   * that structure.  Pathfinding will require efficient use of the map,  *
   * and pulling in unnecessary data with each map cell would add a lot   *
   * of overhead to the memory system.                                    */
  uint8_t hardness[DUNGEON_Y][DUNGEON_X];
  uint8_t pc_distance[DUNGEON_Y][DUNGEON_X];
  uint8_t pc_tunnel[DUNGEON_Y][DUNGEON_X];
  struct characters *characters[DUNGEON_Y][DUNGEON_X];
  pc_t pc;
  uint8_t numMon;
  monster_t *monsters;
} dungeon_t;

void init_dungeon(dungeon_t *d);
void delete_dungeon(dungeon_t *d);
int gen_dungeon(dungeon_t *d);
void render_dungeon(dungeon_t *d);
int write_dungeon(dungeon_t *d, char *file);
int read_dungeon(dungeon_t *d, char *file);
int read_pgm(dungeon_t *d, char *pgm);
void render_distance_map(dungeon_t *d);
void render_tunnel_distance_map(dungeon_t *d);
void render_hardness_map(dungeon_t *d);
void render_movement_cost_map(dungeon_t *d);
void place_monsters(dungeon_t *d);
void sortMonsters(dungeon_t *d);
int living_monsters(dungeon_t *d);
void moveSmart(dungeon_t *d, int index);
void moveMonster(dungeon_t *d, int i);
void moveSmartTunnel(dungeon_t *d, int index);
int is_smart(monster_t m);
int is_telepathic(monster_t m);
int is_tunnel(monster_t m);
int is_erratic(monster_t m);
void movePc(dungeon_t *d);

#endif
