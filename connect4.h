#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool endGame = false;
bool boardFull = false;
string currentPlayer = "X";
string arr[6][7];

HANDLE color = GetStdHandle( STD_OUTPUT_HANDLE );

void defineArr() {
    for (int y=0; y<6; y++) {
        for (int x=0; x<7; x++) {
            arr[y][x] = " ";
        }
    }
}

void onMove() {
    if (!endGame) {
        SetConsoleTextAttribute(color, 7);
        cout << "\n\nPLAYER " << currentPlayer << " on move\n\n";
    }
    else {
        SetConsoleTextAttribute(color, 7);
    }
}

void draw() {
    if (!boardFull) { onMove(); }
    SetConsoleTextAttribute(color, 4);
    for (int x = 0; x < 7; x++) {
        cout << "  " << x+1 << " ";
    }
    cout << " \n";
    SetConsoleTextAttribute(color, 6);
    for (int x = 0; x < 7; x++) {
            cout << "|___";
    }
    cout << "|\n";

    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 7; x++) {
            cout << "|   ";
        }
        cout << "|\n";

        for (int x = 0; x < 7; x++) {
            // cout << "| " << arr[y][x] << " ";
            cout << "| ";
            if (arr[y][x] == "X") {
                SetConsoleTextAttribute(color, 5 | FOREGROUND_INTENSITY);
                cout << arr[y][x] << " ";
                SetConsoleTextAttribute(color, 6);
            }
            else if(arr[y][x] == "O") {
                SetConsoleTextAttribute(color, 2 | FOREGROUND_INTENSITY);
                cout << arr[y][x] << " ";
                SetConsoleTextAttribute(color, 6);
            }
            else { cout << arr[y][x] << " "; }
        }
        // SetConsoleTextAttribute(color, 1);
        cout << "|\n";

        for (int x = 0; x < 7; x++) {
            cout << "|___";
        }
        cout << "|\n";
    }
}

void inArray(int arg) {
    for (int y = 5; y >= 0; y--) {
        // if (arr[y][arg] == "X" || arr[y][arg] == "O") {
        //     continue;
        // }
        if (arr[y][arg] != "X" && arr[y][arg] != "O") {
            arr[y][arg] = currentPlayer;
            return;
        }
    }
}

void toggle() {
    if (currentPlayer == "X") {
        currentPlayer = "O";
    }
    else {
        currentPlayer = "X";
    }
}

void isFull() {
    for (int i = 5; i >= 0; i--) {
        for (int j = 6; j >= 0; j--) {
            if (arr[i][j] == " ") {
                return;
            }
            else if ((i == 0 && j == 0) && (arr[i][j] != " ")) {
                boardFull = true;
                endGame = true;
                system("cls");
                draw();
                std::cout << "\nBOARD FULL -- RESULT: DRAW\n\n";
                abort;
            }
        }
    }
}


void show_winner() {
    SetConsoleTextAttribute(color, FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "\n\nPlayer " << currentPlayer << " is a WINNER!!\n\n";
    endGame = true;
}

// logic function takes *function_pointer as an argument -> in this case show_winner
void logic( void(*fun_ptr)() ) {
    for (int y = 5; y >= 0; y--) {
        for (int x = 0; x <= 3; x++) {
            // rows
            if ((arr[y][x] == arr[y][x+1] &&
                arr[y][x+1] == arr[y][x+2]) &&
                (arr[y][x+2] == arr[y][x+3] &&
                arr[y][x] == currentPlayer)) {
                    fun_ptr();
            }
            // diagonals left -> right
            else if ((arr[y][x] == arr[y-1][x+1] &&
                arr[y-1][x+1] == arr[y-2][x+2]) &&
                (arr[y-2][x+2] == arr[y-3][x+3] &&
                arr[y][x] == currentPlayer)) {
                    fun_ptr();
            }
        }
    }
    // columns
    for (int y = 5; y >= 3; y--) {
        for (int x = 0; x <= 6; x++) {
            if((arr[y][x] == arr[y-1][x] &&
                arr[y-1][x] == arr[y-2][x]) &&
                (arr[y-2][x] == arr[y-3][x] &&
                arr[y][x] == currentPlayer)) {
                    fun_ptr();
            }
        }
    }
    // diagonals right -> left
    for (int y = 5; y >= 0; y--) {
        for (int x = 6; x >= 0; x--) {
            if ((arr[y][x] == arr[y-1][x-1] &&
                arr[y-1][x-1] == arr[y-2][x-2]) &&
                (arr[y-2][x-2] == arr[y-3][x-3] &&
                arr[y][x] == currentPlayer)) {
                    fun_ptr();
            }
        }
    }
}


// usersChoice function takes *function_pointer as an argument which takes another *function_poiner as an argument
void usersChoice( void (*function_1)(void (*function_2)()) ) {
    char col;
    // void (*function_2)() = show_winner;

    SetConsoleTextAttribute(color, 7);
    cout << "\n\nto move:   choose 1 - 7\nto ECS:   any other key";
    cout << "\n\nChoose column:";
    col = getch();
    int ascii = col;
    system("cls");
    if (ascii < 49 || ascii > 55) {
        endGame = true;
    }
    else {
        // arr[5][ascii - 49] = currentPlayer;
        int asc = ascii-49;
        inArray(asc);
    }
    function_1(show_winner);
    // function_1(function_2);
}
