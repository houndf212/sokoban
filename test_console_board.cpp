#include "board.h"
#include "debug_print.h"
#include "consoleboard.h"
#include <iostream>
using namespace std;

void test_console_board()
{
    ElementsMatrix m = ConsoleBoard::from_file("board.txt");

    print(m);

    Board board(m);
    while (!board.is_done()) {
        char c;
        cin>>c;
        switch (c) {
        case 'w':
            board.move(Direction::up);
            break;
        case 's':
            board.move(Direction::down);
            break;
        case 'a':
            board.move(Direction::left);
            break;
        case 'd':
            board.move(Direction::right);
            break;
        default:
            break;
        }
        print(board.to_matrix());
    }
}
