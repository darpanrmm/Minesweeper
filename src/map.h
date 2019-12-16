#ifndef MAP_H
#define MAP_H

#include "main.h"

struct map_elem{
    bool has_mine;
    bool opened;
    bool flagged;
    int num_mines;
};

extern int map_size;

extern int num_mines;

extern struct map_elem *map;
struct map_elem *new_map(int map_size);

struct map_elem *map_get(int i, int j);

void generate_map(int first_move_i, int first_move_j);
void print_map();
void print_open_map();

#endif // MAP_H
