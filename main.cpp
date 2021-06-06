#include <iostream>

#include "inc/game.hh"

using namespace std;

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

int main() {

    //  predefine
    uint size = 4;
    uint need = 3;
    uint depth = 5;

    char AI = O;
    char human = X;
    char first = X;

    /*   *   *   *   *   *   *   *   *   *   */

    char option;
    cout << endl;
    cout << " Wants own parameters? ( y ) :: ";
    cin >> option;
    cout << endl;

    if( option == 'y' || option == 'Y' ) {

        cout << endl;
        cout << " Specify -> [size] [need] [depth] :: ";
        cin >> size >> need >> depth;
        cout << endl;

        cout << endl;
        cout << " Specify -> [AI] [human] [first] :: ";
        cin >> AI >> human >> first;
        cout << endl;
    }

    /*   *   *   *   *   *   *   *   *   *   */

    //  init game
    Game ticTacToe( size, need, depth, AI, human, first );
    ticTacToe.print();

    //  game
    while( !ticTacToe.isGameOver() ) {
        ticTacToe.turn();
    }

    //  prints result
    ticTacToe.result();
}