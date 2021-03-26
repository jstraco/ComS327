#ifndef IO_H
# define IO_H

typedef class dungeon dungeon_t;

void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(dungeon_t *d);
void io_handle_input(dungeon_t *d);
void io_queue_message(const char *format, ...);
void io_display_dungeon(dungeon_t *d);
void teleport_mode(dungeon_t *d);
void render_teleport_dungeon(dungeon_t *d,int destx,int desty);

#endif
