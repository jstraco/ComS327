#ifndef BOSS_H
#define BOSS_H

#include "dims.h"

typedef enum bullet_type
{
    horizontal,
    vertical
} bullet_type_t;

int BOARD_X = 20;
int BOARD_Y = 20;

pair_t position;

class bullet
{
public:
    pair_t position;
    bullet_type_t type;
    int direction;
    int bouncy;
    int alive = 1;
};

int final_battle(uint32_t dead);
int select_round(int round);
int play_round(int bulletCount, bullet bullets[40]);
int validate_pass(char c);
void update_board(bullet bullets[40]);

#endif