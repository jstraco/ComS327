#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
# include <cstdlib>
# include <cstdint>
# include <vector>
#include <string>
#include <unistd.h>

#include "boss.h"
#include "io.h"
#include "descriptions.h"

int final_battle(uint32_t dead) {
    int roundCount = ((int) dead) % 10;
    if(roundCount > 3) roundCount = 3;
    clear();
    mvprintw(7, 15, "You thought this madness was over...");
    mvaddch(8, 32, 'o');
    mvprintw(9, 30, "<( )>");
    mvprintw(10, 31, "/ \\");
    mvprintw(11, 25, "Oh no, it's Big J!");
    mvprintw(12, 10, "If you void his attacks and reach the finish line, you may just get out alive!");
    mvprintw(13, 15, "Because you killed %u monsters, there will be %d rounds.", dead, 4 - roundCount);
    mvprintw(14, 25, "Press any key to continue.");

    refresh();
    getch();
    int still_alive;
    for(int i = roundCount; i <= 3; i++) {
        still_alive = select_round(i);
        if(!still_alive)
            break;
    }
    clear();
    if(still_alive) {
        mvaddch(8, 32, '\\');
        mvprintw(9,31,"/(");
        mvaddch(10, 33, 'o');
        mvprintw(11,31,")\\");
        mvaddch(12, 32, '/');
        mvprintw(14, 25, "You survived the dungeon!");
    }
    else {
        mvaddch(7, 32, 'M');
        mvaddch(8, 32, 'o');
        mvprintw(9, 30, "<( )>");
        mvprintw(10, 31, "/ \\");
        if(still_alive == -1) {
            mvprintw(14, 25, "You fell off the edge of the world...");
        }
        else {
            mvprintw(14, 25, "You were struck by a bullet...");
        }
    }
    getch();
    refresh();
    return still_alive;
}

int select_round(int round) {
    bullet bullets[40];
    int bulletCount;
    switch(round) {
        case 0:
        {
            bulletCount = BOARD_Y - 6;
            for(int i = 0; i < bulletCount; i++) {
                bullets[i].type = vertical;
                bullets[i].bouncy = 0;
                bullets[i].direction = 1;
            }
            int i = 0;
            for(int y = BOARD_Y - 1, x = 0; i < bulletCount / 2; y--, x++) {
                bullets[i].position[dim_y] = y;
                bullets[i].position[dim_x] = x;
            }
            for(int y = BOARD_Y / 2, x = BOARD_X - 1; i < bulletCount; y--, x--) {
                bullets[i].position[dim_y] = y;
                bullets[i].position[dim_x] = x;
            }
            break;
        }
        case 1:
        {
            bulletCount = BOARD_Y;
            for(int i = 0; i < bulletCount; i++) {
                bullets[i].type = vertical;
                bullets[i].bouncy = 1;
                bullets[i].direction = 1;
            }
            for(int i = 0; i < bulletCount; i++) {
                int y = 1;
                if(i < 6 && i > 13) {
                    y = BOARD_Y - 1;
                }
                bullets[i].position[dim_y] = y;
                bullets[i].position[dim_x] = i;
            }
            break;
        }
        case 2:
        {
            bulletCount = BOARD_X - 4;
            for(int i = 0; i < bulletCount / 2; i++) {
                bullets[i].type = horizontal;
                bullets[i].bouncy = 1;
                bullets[i].direction = 1;
            }
            for(int i = 8; i < bulletCount; i++) {
                bullets[i].type = horizontal;
                bullets[i].bouncy = 1;
                bullets[i].direction = -1;
            }
            //TODO: place bullets
            break;
        }
        case 3:
        {
            bulletCount = 16;
            for(int i = 0; i < bulletCount / 2; i++) {
                bullets[i].type = horizontal;
                bullets[i].bouncy = 1;
                bullets[i].direction = 1;
            }
            for(int i = 8; i < bulletCount; i++) {
                bullets[i].type = horizontal;
                bullets[i].bouncy = 1;
                bullets[i].direction = -1;
            }
            //TODO: place bullets
            break;
        }
        default:
            clear();
            mvprintw(7, 15, "Round Error");
            refresh();
            getch();
            break;
    }
    return play_round(bulletCount, bullets);
}

void update_board(bullet bullets[40]) {
    clear();
    //TODO
    refresh();
}

int play_round(int bulletCount, bullet bullets[40]) {
    nodelay(stdscr, TRUE);
    char userInput;
    time_t bulletTurn = time(NULL);
    int userResponseTurn = 0;
    while(1) {
        if (validate_pass(userInput = getch())) {
            if(userResponseTurn || (time(NULL) - bulletTurn) > 3) {
                for(int i = 0; i < bulletCount; i++) {
                    if(!bullets[i].alive) {
                        continue;
                    }
                    if(bullets[i].type == vertical){
                        bullets[i].position[dim_y] += bullets[i].direction;
                    }
                    else {
                        bullets[i].position[dim_x] += bullets[i].direction;
                    }
                    if(bullets[i].position[dim_y] == position[dim_y] || bullets[i].position[dim_y] == position[dim_y]) {
                        return -2;
                    }
                    if(bullets[i].position[dim_y] <= 0 || bullets[i].position[dim_y] >= BOARD_Y || bullets[i].position[dim_x] < 0 || bullets[i].position[dim_x] >= BOARD_X) {
                        if(bullets[i].bouncy) {
                            bullets[i].direction = -bullets[i].direction;
                            if(bullets[i].type == vertical){
                                bullets[i].position[dim_y] += bullets[i].direction;
                            }
                            else {
                                bullets[i].position[dim_x] += bullets[i].direction;
                            }
                        }
                        else {
                            bullets[i].alive = 0;
                            continue;
                        }
                    }
                    for(int j = 0; j < bulletCount; j++) {
                        if(i == j || !bullets[j].alive) {
                            continue;
                        }
                        if(bullets[i].position[dim_y] == bullets[j].position[dim_y] || bullets[i].position[dim_y] == bullets[j].position[dim_y]) {
                            if(bullets[i].bouncy) {
                                bullets[i].direction = -bullets[i].direction;
                                if(bullets[i].type == vertical) {
                                    bullets[i].position[dim_y] += bullets[i].direction;
                                }
                                else {
                                    bullets[i].position[dim_x] += bullets[i].direction;
                                }
                            }
                            else {
                                bullets[i].alive = 0;
                                break;
                            }
                            if(bullets[j].bouncy) {
                                bullets[j].direction = -bullets[j].direction;
                            }
                            else {
                                bullets[j].alive = 0;
                                continue;
                            }
                        }
                    }
                }
                userResponseTurn = 0;
                update_board(bullets);
                bulletTurn = time(NULL);
            }
        }
        else {
            int key;
            switch(userInput) {
            case '7':
            case 'y':
            case KEY_HOME:
                key = 7;
                break;
            case '8':
            case 'k':
            case KEY_UP:
                key = 8;
                break;
            case '9':
            case 'u':
            case KEY_PPAGE:
                key = 9;
                break;
            case '6':
            case 'l':
            case KEY_RIGHT:
                key = 6;
                break;
            case '3':
            case 'n':
            case KEY_NPAGE:
                key = 3;
                break;
            case '2':
            case 'j':
            case KEY_DOWN:
                key = 2;
                break;
            case '1':
            case 'b':
            case KEY_END:
                key = 1;
                break;
            case '4':
            case 'h':
            case KEY_LEFT:
                key = 4;
                break;
            case '5':
            case ' ':
            case '.':
            case KEY_B2:
                key = 0;
                break;
            }
            switch (key) {
            case 1:
            case 2:
            case 3:
                position[dim_y]++;
                break;
            case 4:
            case 5:
            case 6:
                break;
            case 7:
            case 8:
            case 9:
                position[dim_y]--;
                break;
            }
            switch (key) {
            case 1:
            case 4:
            case 7:
                position[dim_x]--;
                break;
            case 2:
            case 5:
            case 8:
                break;
            case 3:
            case 6:
            case 9:
                position[dim_x]++;
                break;
            }
            if(position[dim_y] >= BOARD_Y || position[dim_x] < 0 || position[dim_x] >= BOARD_X) {
                return -1;
            }
            for(int i = 0; i < bulletCount; i++) {
                if(!bullets[i].alive) {
                    continue;
                }
                if(bullets[i].position[dim_y] == position[dim_y] || bullets[i].position[dim_y] == position[dim_y]) {
                    return -2;
                }
            }
            if(position[dim_y] == 0) return 1;
            while(getch() != ERR);
            userResponseTurn = 1;
        }
    }
}

int validate_pass(char c) {
    return(c == ERR || (
        c != '1' &&
        c != '2' &&
        c != '3' &&
        c != '4' &&
        c != '5' &&
        c != '6' &&
        c != '7' &&
        c != '8' &&
        c != '9' &&
        c != 'y' &&
        c != 'k' &&
        c != 'u' &&
        c != 'l' &&
        c != 'n' &&
        c != 'j' &&
        c != 'b' &&
        c != 'h' &&
        c != ' ' &&
        c != '.' &&
        c != KEY_HOME &&
        c != KEY_UP &&
        c != KEY_PPAGE &&
        c != KEY_RIGHT &&
        c != KEY_NPAGE &&
        c != KEY_DOWN &&
        c != KEY_END &&
        c != KEY_LEFT &&
        c != KEY_B2
    ));
}