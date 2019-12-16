#include "map.h"

int num_mines;
int map_size;

struct map_elem *map;
struct map_elem *map_get(int i, int j){
    return &map[i*map_size + j];
}

struct map_elem *new_map(int map_size){
    return new struct map_elem[map_size*map_size]();
}

int mines_in_cell(int i, int j){
    if (i >= 0 && i < map_size && j >= 0 && j < map_size && map_get(i, j)->has_mine)
    return 1;
    else
    return 0;
}

int count_mines (int i, int j){
    int ile = 0;
    if (!map_get(i, j)->has_mine){
        ile += mines_in_cell(i, j-1);
        ile += mines_in_cell(i-1, j);
        ile += mines_in_cell(i-1, j-1);
        ile += mines_in_cell(i+1, j-1);
        ile += mines_in_cell(i+1, j);
        ile += mines_in_cell(i-1, j+1);
        ile += mines_in_cell(i, j+1);
        ile += mines_in_cell(i+1, j+1);
    }

    return ile;
}


void generate_map(int first_move_i, int first_move_j){
    for (int i = 0; i < num_mines; i++){
        int row, col;
        do {
            row = rand() % map_size;
            col = rand() % map_size;
        } while ((row == first_move_i && col == first_move_j) || (map_get(row, col)->has_mine));
        map_get(row, col)->has_mine = true;
    }

    for (int i = 0; i < map_size; ++i){
        for (int j = 0; j < map_size; ++j){
            map_get(i, j)->num_mines = count_mines(i, j);
        }
    }

    remaining_cells = map_size*map_size - num_mines;
    remaining_mines = num_mines;
}


void print_map(){
    cout << endl;
    int c = 1;
    cout << "   ";
    if (map_size < 10){
        for (int q = 1; q <= map_size; q++)
            cout << q << "  ";
    }
    else{
        for (int q = 1; q < 10; ++q)
            cout << q << "  ";
        for (int q = 10; q <= map_size; q++)
            cout << q << " ";
    }
    cout << endl;

    for (int i = 0; i < map_size; i++){
        cout << c;
        if (c < 10)
            cout << "  ";
        else cout << " ";
        ++c;
        for (int j = 0; j < map_size; j++){
            if ((map_get(i, j)->opened) && (map_get(i, j)->has_mine)){
                HANDLE  hConsole;
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, RED);
                cout << "B  ";
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            else if ((map_get(i, j)->opened) && (!map_get(i, j)->has_mine)){
                cout << map_get(i, j)->num_mines << "  ";
            }
            else if ((map_get(i, j)->flagged) && (!map_get(i, j)->opened)){
                HANDLE  hConsole;
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, GREEN);
                cout << "F  ";
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            else{
                HANDLE  hConsole;
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, VIOL);
                cout << "X  ";
                SetConsoleTextAttribute(hConsole, WHITE);
            }
        }
        cout << endl << endl;
    }
}

void _map(){
    for (int i = 0; i < map_size; i++){
        for (int j = 0; j < map_size; j++){
            if (map_get(i, j)->has_mine){
                cout << "B";
            }
            else if (!map_get(i, j)->has_mine){
                cout << map_get(i, j)->num_mines;
            }
        }
        cout << endl;
    }
}
