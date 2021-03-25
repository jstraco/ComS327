#ifndef PC_H
# define PC_H


# include <stdint.h>

# include "dims.hpp"
typedef struct dungeon dungeon_t;

typedef class pc {
} pc_t;

void pc_delete(pc_t *pc);
uint32_t pc_is_alive(dungeon_t *d);
void config_pc(dungeon_t *d);
uint32_t pc_next_pos(dungeon_t *d, pair_t dir);
void place_pc(dungeon_t *d);
uint32_t pc_in_room(dungeon_t *d, uint32_t room);
//void pc_updateSeen(dungeon_t *d);
//void pc_init_mapSeen(dungeon_t *d);

#endif
