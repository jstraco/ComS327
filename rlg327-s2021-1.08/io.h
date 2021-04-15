#ifndef IO_H
# define IO_H

class dungeon;

void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(dungeon *d);
void io_handle_input(dungeon *d);
void io_queue_message(const char *format, ...);
void io_list_inv(dungeon *d);
void io_list_equipment(dungeon *d);
void io_inspect_item(dungeon *d);
void io_delete_item(dungeon *d);
void io_drop_item(dungeon *d);
void io_unequip_item(dungeon *d);
void io_equip_item(dungeon *d);
void io_look_monster(dungeon *d);
const char * io_inv_item_name(dungeon *d, int item);
const char * io_equipment_item_name(dungeon *d, int item);

#endif
