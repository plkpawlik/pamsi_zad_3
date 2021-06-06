#include "board.hh"

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

class Game {
    
    private:

        Board * board;      //  game board

        string message;     //  global message variable

        bool gameOver;
        bool gameTie;
        bool gameWin;

        char player;        //  who now plays
        char player_AI;     //  AI variable
        char player_human;  //  human variable

        int depth;
        int size;
        int need;

    public:

        Game( uint size, uint need, char human, char AI, char first, int depth );
        ~Game();

        bool insert( coord c );
        bool isGameOver();
        bool isGameTie();
        bool isGameWin();

        void result();
        void print();
        void turn();

        coord getBestMove();
        coord getMove();

        int minimax( int depth, bool AI );
};
