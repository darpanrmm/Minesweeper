#include "saveload.h"

void save_game(string filename){
    ofstream f;
    f.open(filename.c_str());
    f << remaining_cells << " ";
    f << remaining_mines << " ";
    f << first_move_made << " ";
    f << start_time << " ";
    f << map_size << " ";
    f << num_mines << " ";
    for (int i = 0; i < map_size; i++){
        for (int j = 0; j < map_size; j++){
            f << map_get(i,j)->has_mine << " ";
            f << map_get(i,j)->opened << " ";
            f << map_get(i,j)->flagged << " ";
            f << map_get(i,j)->num_mines << " ";
        }
    }
    f.close();
}

void load_game(string filename){
    ifstream f;
    f.open(filename.c_str());
    f >> remaining_cells;
    f >> remaining_mines;
    f >> first_move_made;
    f >> start_time;
    f >> map_size;
    f >> num_mines;
    map = new_map(map_size);
    for (int i = 0; i < map_size; i++){
        for (int j = 0; j < map_size; j++){
            f >> map_get(i,j)->has_mine;
            f >> map_get(i,j)->opened;
            f >> map_get(i,j)->flagged;
            f >> map_get(i,j)->num_mines;
            if ((map_get(i,j)->has_mine) && (map_get(i,j)->opened)){
                cout << map_get(i,j)->has_mine << " " << map_get(i,j)->opened << "";
            }
        }
    }
    f.close();
}
