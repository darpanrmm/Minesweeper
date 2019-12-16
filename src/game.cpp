#include "game.h"

int remaining_cells;
int remaining_mines;
int start_time;
bool first_move_made = false;

void open(int i, int j){
    if ((i>=0) && (i<map_size) && (j>=0) && (j<map_size)){
        if ((!map_get(i, j)->opened) && (!map_get(i, j)->has_mine)){
            if (map_get(i, j)->flagged){
                remaining_mines++;
            }
            map_get(i, j)->opened = true;
            remaining_cells--;
            if (map_get(i, j)->num_mines == 0){
                open(i,j-1);
                open(i-1,j);
                open(i-1,j-1);
                open(i+1,j-1);
                open(i+1,j);
                open(i-1,j+1);
                open(i,j+1);
                open(i+1,j+1);
            }
        }
    }
}

void flag(int i, int j){
    if ((i>=0) && (i<map_size && (j>=0) && (j<map_size))){
        if ((!map_get(i, j)->flagged) && (!map_get(i, j)->opened)){
            map_get(i, j)->flagged = true;
            remaining_mines--;
        }
    }
}

int press(){
    int i, j;
    char c;
    cout << "save, flag or open? (s, f, o)" << endl;
    cin >> c;
    if (c == 's'){
        cin.ignore(10, '\n');
        string filename;
        cout << "Filename: ";
        getline(cin, filename);
        save_game(filename);
    }
    else{
        cout << "Input coordinates: " << endl;
        cout << "row=";
        cin >> i;
        cout << "column=";
        cin >> j;
        if ((i > map_size) && (j > map_size) && (i < 0) && (j < 0))
            goto continue_game;
        i--;
        j--;
    }
    if (c == 'o'){
        if (!first_move_made){
            generate_map(i, j);
            first_move_made = true;
        }
        if (!map_get(i, j)->opened){
            open(i, j);
            if (remaining_cells ==  0){
                return WIN;
            }
            if (map_get(i, j)->has_mine){
                map_get(i, j)->opened = true;
                HANDLE  hConsole;
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, RED);
                cout << "FAIL!!" << endl;
                SetConsoleTextAttribute(hConsole, WHITE);
                print_stats();
                system("pause");
                cout<<"Print any key...";
                cin.get();
                return DIE;
            }
            else goto continue_game;
        }
        else{
            goto continue_game;
        }
    }

    else if (c == 'f'){
        if (!first_move_made){
            generate_map(i, j);
            first_move_made = true;
        }
        if ((!map_get(i, j)->opened) && (!map_get(i, j)->flagged)){
            flag(i,j);
        }
        goto continue_game;
    }

    else if (c != 's'){
        cout << "error" << endl;
        cout << map_get(i, j)->opened << " " << map_get(i, j)->flagged << " " << map_get(i, j)->has_mine << endl;
        goto continue_game;
    }

continue_game:
    print_stats();
    return CONTINUE;
}

void print_stats(){
    cout <<  endl << "THERE ARE " << remaining_cells << " CELLS LEFT" << endl;
    cout << "THERE ARE " << remaining_mines << " MINES LEFT" << endl;
    cout << "GAME TIME: " << time(NULL) - start_time << " sec" << endl;
}
