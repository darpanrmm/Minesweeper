#include "main.h"

int main(){
    int result;
    char start;
    cout << "New game or load? (n, l)" <<  endl;
    cin >> start;
    if (start == 'l'){
        cin.ignore(10, '\n');
        string filename;
        cout << "Filename: ";
        getline(cin, filename);
        load_game(filename);
        print_map();
    }
    else{
        cout << "Input map size: ";
        cin >> map_size;
        cout << "Input count of mines";
        cout << " (not more than " << map_size*map_size-1 << "): ";
        cin >> num_mines;
        if ((num_mines < 1) && (num_mines > map_size*map_size-1))
            cout << "error";
        map = new_map(map_size);
        int seed = time(NULL);
        srand(seed);
        start_time = time(NULL);
    }

        do{
            cout << endl;
            print_map();
        }while ((result = press()) == CONTINUE);

    if (result == WIN){
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, GREEN);
        cout << "WIN!!" << endl;
        SetConsoleTextAttribute(hConsole, WHITE);
    }
    print_map();
    delete [] map;

    return 0;
}

