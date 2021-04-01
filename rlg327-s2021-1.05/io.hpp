#ifndef IO_H
# define IO_H
#include <string>

typedef class dungeon dungeon_t;

void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(dungeon_t *d);
void io_handle_input(dungeon_t *d);
void io_queue_message(const char *format, ...);
void io_display_dungeon(dungeon_t *d);
void teleport_mode(dungeon_t *d);
void render_teleport_dungeon(dungeon_t *d,int destx,int desty);
void io_read_npc(dungeon_t *d);
int dice_roll(std::string dice);
int get_color(std::string color);

#endif
