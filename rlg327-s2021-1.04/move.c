#include "move.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include <curses.h>
#include "dungeon.h"
#include "heap.h"
#include "move.h"
#include "npc.h"
#include "pc.h"
#include "character.h"
#include "utils.h"
#include "path.h"
#include "event.h"

void do_combat(dungeon_t *d, character_t *atk, character_t *def)
{
  if (def->alive) {
    def->alive = 0;
    if (def != &d->pc) {
      d->num_monsters--;
    }
    atk->kills[kill_direct]++;
    atk->kills[kill_avenged] += (def->kills[kill_direct] +
                                  def->kills[kill_avenged]);
  }
}

void move_character(dungeon_t *d, character_t *c, pair_t next)
{
  if (charpair(next) &&
      ((next[dim_y] != c->position[dim_y]) ||
       (next[dim_x] != c->position[dim_x]))) {
    do_combat(d, c, charpair(next));
  } else {
    /* No character in new position. */

    d->character[c->position[dim_y]][c->position[dim_x]] = NULL;
    c->position[dim_y] = next[dim_y];
    c->position[dim_x] = next[dim_x];
    d->character[c->position[dim_y]][c->position[dim_x]] = c;
  }
}

void do_moves(dungeon_t *d)
{
  pair_t next;
  character_t *c;
  event_t *e;
  

  /* Remove the PC when it is PC turn.  Replace on next call.  This allows *
   * use to completely uninit the heap when generating a new level without *
   * worrying about deleting the PC.                                       */

  if (pc_is_alive(d)) {
    /* The PC always goes first one a tie, so we don't use new_event().  *
     * We generate one manually so that we can set the PC sequence       *
     * number to zero.                                                   */
    e = malloc(sizeof (*e));
    e->type = event_character_turn;
    /* Hack: New dungeons are marked.  Unmark and ensure PC goes at d->time, *
     * otherwise, monsters get a turn before the PC.                         */
    if (d->is_new) {
      d->is_new = 0;
      e->time = d->time;
    } else {
      e->time = d->time + (1000 / d->pc.speed);
    }
    e->sequence = 0;
    e->c = &d->pc;
    heap_insert(&d->events, e);
  }

  while (pc_is_alive(d) &&
         (e = heap_remove_min(&d->events)) &&
         ((e->type != event_character_turn) || (e->c != &d->pc))) {
    d->time = e->time;
    if (e->type == event_character_turn) {
      c = e->c;
    }
    if (!c->alive) {
      if (d->character[c->position[dim_y]][c->position[dim_x]] == c) {
        d->character[c->position[dim_y]][c->position[dim_x]] = NULL;
      }
      if (c != &d->pc) {
        event_delete(e);
      }
      continue;
    }

    npc_next_pos(d, c, next);
    move_character(d, c, next);

    heap_insert(&d->events, update_event(d, e, 1000 / c->speed));
  }

  if (pc_is_alive(d) && e->c == &d->pc) {
    c = e->c;
    d->time = e->time;
    /* Kind of kludgey, but because the PC is never in the queue when   *
     * we are outside of this function, the PC event has to get deleted *
     * and recreated every time we leave and re-enter this function.    */
    e->c = NULL;
    event_delete(e);
    //pc_next_pos(d, next);
    
    do_input(d, c, getch());
    // next[dim_x] += c->position[dim_x];
    // next[dim_y] += c->position[dim_y];
    // if (mappair(next) <= ter_floor) {
    //   mappair(next) = ter_floor_hall;
    //   hardnesspair(next) = 0;
    // }
    //move_character(d, c, next);

    dijkstra(d);
    dijkstra_tunnel(d);
  }
}

void dir_nearest_wall(dungeon_t *d, character_t *c, pair_t dir)
{
  dir[dim_x] = dir[dim_y] = 0;

  if (c->position[dim_x] != 1 && c->position[dim_x] != DUNGEON_X - 2) {
    dir[dim_x] = (c->position[dim_x] > DUNGEON_X - c->position[dim_x] ? 1 : -1);
  }
  if (c->position[dim_y] != 1 && c->position[dim_y] != DUNGEON_Y - 2) {
    dir[dim_y] = (c->position[dim_y] > DUNGEON_Y - c->position[dim_y] ? 1 : -1);
  }
}

uint32_t against_wall(dungeon_t *d, character_t *c)
{
  return ((mapxy(c->position[dim_x] - 1,
                 c->position[dim_y]    ) == ter_wall_immutable) ||
          (mapxy(c->position[dim_x] + 1,
                 c->position[dim_y]    ) == ter_wall_immutable) ||
          (mapxy(c->position[dim_x]    ,
                 c->position[dim_y] - 1) == ter_wall_immutable) ||
          (mapxy(c->position[dim_x]    ,
                 c->position[dim_y] + 1) == ter_wall_immutable));
}

uint32_t in_corner(dungeon_t *d, character_t *c)
{
  uint32_t num_immutable;

  num_immutable = 0;

  num_immutable += (mapxy(c->position[dim_x] - 1,
                          c->position[dim_y]    ) == ter_wall_immutable);
  num_immutable += (mapxy(c->position[dim_x] + 1,
                          c->position[dim_y]    ) == ter_wall_immutable);
  num_immutable += (mapxy(c->position[dim_x]    ,
                          c->position[dim_y] - 1) == ter_wall_immutable);
  num_immutable += (mapxy(c->position[dim_x]    ,
                          c->position[dim_y] + 1) == ter_wall_immutable);

  return num_immutable > 1;
}
void do_input(dungeon_t *d, character_t *c, int ch){
  pair_t dir;
  switch(ch){
    case 'q':
    d->pc.alive = 0;
    break;
    case 7 + '0': 
    case 'y':
    dir[dim_y] = c->position[dim_y] - 1;
    dir[dim_x] = c->position[dim_x] - 1;
    move_pc(d, c, dir);
    break;
    case 8 + '0': 
    case 'k':
    dir[dim_y] = c->position[dim_y] - 1;
    dir[dim_x] = c->position[dim_x];
    move_pc(d, c, dir);
    break;
    case 9 + '0': 
    case 'u':
    dir[dim_y] = c->position[dim_y] - 1;
    dir[dim_x] = c->position[dim_x] + 1;
    move_pc(d, c, dir);
    break;
    case 3 + '0': 
    case 'n':
    dir[dim_y] = c->position[dim_y] + 1;
    dir[dim_x] = c->position[dim_x] + 1;
    move_pc(d, c, dir);
    break;
    case 2 + '0': 
    case 'j':
    dir[dim_y] = c->position[dim_y] + 1;
    dir[dim_x] = c->position[dim_x];
    move_pc(d, c, dir);
    break;
    case 1 + '0': 
    case 'b':
    dir[dim_y] = c->position[dim_y] + 1;
    dir[dim_x] = c->position[dim_x] - 1;
    move_pc(d, c, dir);
    break;
    case 4 + '0': 
    case 'h':
    dir[dim_y] = c->position[dim_y];
    dir[dim_x] = c->position[dim_x] - 1;
    move_pc(d, c, dir);
    break;
    case 6 + '0': 
    case 'l': 
    dir[dim_y] = c->position[dim_y];
    dir[dim_x] = c->position[dim_x] + 1;
    move_pc(d, c, dir);
    break;
    case '<':
    case '>':
    if(d->map[c->position[dim_y]][c->position[dim_x]] == ter_stairs_down 
    || d->map[c->position[dim_y]][c->position[dim_x]] == ter_stairs_up){
      delete_dungeon(d);
      init_dungeon(d);
      gen_dungeon(d);
      config_pc(d);
      gen_monsters(d);
    }
    break;
    case ' ':
    case 5 + '0':
    //nothing to do here, just doesn't move
    break;
    case 'm':
    monster_list(d);
    break;
    default: ;
    WINDOW * win = newwin(1, 81, 23, 0);
    wprintw(win, "not a valid input, turn skiped");
    wrefresh(win);
    break;
  }
}
uint32_t do_error(){
  WINDOW * win = newwin(1, 81, 23, 0);
  wprintw(win, "There's a wall in the way!");
  wrefresh(win);
  return 0;
}

void monster_list(dungeon_t *d)
{
  pair_t p;
  WINDOW *monWin = newwin(20, 81, 23, 0);
  char **list = malloc(d->num_monsters * sizeof(char *));
  int i = 0;
  for (p[dim_y] = 0; p[dim_y] < DUNGEON_Y; p[dim_y]++)
  {
    for (p[dim_x] = 0; p[dim_x] < DUNGEON_X; p[dim_x]++)
    {
      if (charpair(p) && charpair(p)->symbol != '@')
      {
        list[i] = malloc(24 * sizeof(char));
        char *yDirection = malloc(5 * sizeof(char));
        int yDistance;
        if (d->pc.position[dim_y] >= p[dim_y])
        {
          yDirection = "North";
          yDistance = d->pc.position[dim_y] - p[dim_y];
        }
        else
        {
          yDirection = "South";
          yDistance = p[dim_y] - d->pc.position[dim_y];
        }
        char *xDirection = malloc(4 * sizeof(char));
        int xDistance;
        if (d->pc.position[dim_x] >= p[dim_x])
        {
          xDirection = "West";
          xDistance = d->pc.position[dim_x] - p[dim_x];
        }
        else
        {
          xDirection = "East";
          xDistance = p[dim_x] - d->pc.position[dim_x];
        }
        sprintf(list[i], "%c, %d %s and %d %s", charpair(p)->symbol, yDistance, yDirection, xDistance, xDirection);
        i++;
      }
    }
  }
  int listMax = 10;
  if (i < d->num_monsters)
  {
    listMax = d->num_monsters;
  }
  i = 0;
  while (i >= 0)
  {
    for (i = 0; i < listMax; i++)
    {
      wprintw(monWin, "%s\n", list[i]);
    }
    wrefresh(monWin);
    int monCH = getch();
    switch (monCH)
    {
    case KEY_DOWN:
      if (i + listMax < listMax)
      {
        i++;
      }
      break;
    case KEY_UP:
      if (i < 0)
      {
        i--;
      }
      break;
    default:
      i = -1;
      break;
    }
  }
  delwin(monWin);
  free(list);
}