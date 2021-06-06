#include "../inc/game.hh"

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

Game::Game( uint size, uint need, uint depth, char AI, char human, char first ) {

    this->board = new Board( size, need );

    this->depth = depth;
    this->size = size;
    this->need = need;

    this->player_human = human;
    this->player_AI = AI;
    this->player = first;

    this->gameOver = false;
    this->gameTie = false;
    this->gameWin = false;
}

Game::~Game() {

}

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

bool Game::insert( coord c ) {
    
    //  tests move
    if( this->board->isEmpty( c ) ) {

        //  inserts value
        this->board->board[ c.row ][ c.col ] = this->player;

        //  tests results
        if( this->board->isWin( player ) ) {

            this->message = " Win has been detected! ";
            this->gameOver = true;
            this->gameTie = false;
            this->gameWin = true;

            return true;
        }

        if( this->board->isTie( player ) ) {

            this->message = " Tie has been detected! ";
            this->gameOver = true;
            this->gameTie = true;
            this->gameWin = false;

            return true;
        }

        //  no win or tie
        this->player = ( this->player == this->player_AI ) ? this->player_human : this->player_AI;
        this->message = "";

        this->gameOver = false;
        this->gameTie = false;
        this->gameWin = false;


        //  procedure ok
        return true;
    }

    //  proccedure not okay
    return false;
}

bool Game::isGameOver() {
    return this->gameOver;
}

bool Game::isGameTie() {
    return this->gameTie;
}

bool Game::isGameWin() {
    return this->gameWin;
}

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

void Game::result() {

    cout << endl;
    cout << " Player -> " << this->player << " <- finishes with a " << ( this->gameWin ? " Win! " : " Tie! ") << endl;
    cout << endl;
}

void Game::print() {

    //  clears console
    system( "clear" );

    //  prints updated board
    this->board->printAll();

    //  prints current info message
    cout << endl;
    cout << "   " << this->player_human << " :: player Human " << endl;
    cout << "   " << this->player_AI << " :: player A.I. " << endl;
    cout << endl;
    cout << " info: " << this->message << endl;
    cout << endl;
}

void Game::turn() {

    //  turn selector
    if( this->player == this->player_AI ) {
        while( !this->insert( this->getBestMove() ));
    } else {
        while( !this->insert( this->getMove() ));
    }

    //  prints all needed data
    this->print();
}

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

coord Game::getBestMove() {

    uint row = P_INF;
    uint col = P_INF;
    int best = N_INF;

    /*   *   *   *   *   *   *   *   *   *   */

    for( uint i = 0; i < this->board->size; i++ ) {
        for( uint j = 0; j < this->board->size; j++ ) {

            //  tests for possible moves
            if( this->board->isEmpty({ i, j }) ) {

                //  tests move
                this->board->board[i][j] = this->player_AI;

                int score = this->minimax( 0, false );

                //  better move detected
                if( score > best ) {
                    best = score;
                    row = i;
                    col = j;
                }

                //  restores move
                this->board->board[i][j] = EMPTY;
            }
        }
    }
    
    /*   *   *   *   *   *   *   *   *   *   */

    return { row, col };
}

coord Game::getMove() {

    uint row = P_INF;
    uint col = P_INF;

    cout << endl;
    cout << " Specify -> [row] [column] :: ";
    cin >> row >> col;
    cout << endl;

    return { row, col };
}

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

int Game::minimax( uint depth, bool AI ) {

    //  terminal states & depth control
    if( depth > this->depth )   { return TIE; }

    if( this->board->isWin( this->player_human ) )  { return DEF; }
    if( this->board->isWin( this->player_AI ) )     { return WIN; }
    if( this->board->isTie( this->player_AI ) )     { return TIE; }

    /*   *   *   *   *   *   *   *   *   *   */
    if( AI ) {  //  MAXIMIZE
    /*   *   *   *   *   *   *   *   *   *   */

        int best = N_INF;

        for( uint i = 0; i < this->board->size; i++ ) {
            for( uint j = 0; j < this->board->size; j++ ) {

                //  tests for possible moves
                if( this->board->isEmpty({ i, j }) ) {

                    //  tests move
                    this->board->board[i][j] = this->player_AI;

                    int score = this->minimax( depth + 1, false );

                    //  better move detected
                    if( score > best ) {
                        best = score;
                    }

                    //  restores move
                    this->board->board[i][j] = EMPTY;
                }
            }
        }

        return best;

    /*   *   *   *   *   *   *   *   *   *   */
    } else {        //  MINIMIZE
    /*   *   *   *   *   *   *   *   *   *   */

        int worst = P_INF;

        for( uint i = 0; i < this->board->size; i++ ) {
            for( uint j = 0; j < this->board->size; j++ ) {

                //  tests for possible moves
                if( this->board->isEmpty({ i, j }) ) {

                    //  tests move
                    this->board->board[i][j] = this->player_human;

                    int score = this->minimax( depth + 1, true );

                    //  better move detected
                    if( score < worst ) {
                        worst = score;
                    }

                    //  restores move
                    this->board->board[i][j] = EMPTY;
                }
            }
        }

        return worst;
    }
    /*   *   *   *   *   *   *   *   *   *   */
}