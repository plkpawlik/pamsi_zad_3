#include <iostream>

#include "inc/game.hh"

using namespace std;

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

int main() {

    //  init game
    Game ticTacToe( 4, 3, X, O, X, 6 );
    ticTacToe.print();

    //  game
    while( !ticTacToe.isGameOver() ) {
        ticTacToe.turn();
    }

    //  prints result
    ticTacToe.result();
}