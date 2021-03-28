
#include "connect4.h"

int main() {

    system("cls");
    defineArr();
    draw();
    std::cout << "\nWELCOME\n";

    while (endGame == false) {
        usersChoice(logic);
        toggle();
        draw();
        isFull();
    }

    cout << endl;
    SetConsoleTextAttribute(color, 7);
    system("pause");

    return 0;
}