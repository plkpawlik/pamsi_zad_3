#include <iostream>

#include "inc/game.hh"

using namespace std;

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

int main() {

    //  predefine
    uint size = 5;
    uint need = 4;
    uint depth = 3;

    char AI = O;
    char human = X;
    char first = O;

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