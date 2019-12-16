#ifndef GAME_H
#define GAME_H

#include "main.h"

#define CONTINUE 0
#define DIE 1
#define WIN 2

extern int remaining_cells;
extern int remaining_mines;
extern int start_time;
extern bool first_move_made;

int press();
void print_stats();

#endif // GAME_H
