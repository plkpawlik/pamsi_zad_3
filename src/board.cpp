#include "../inc/board.hh"

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

Board::Board( uint size, uint need ) {

    this->size = size;
    this->need = need;

    this->board = new char * [ size ];

    for( uint i = 0; i < this->size; i++ ) {
        this->board[i] = new char [ size ];
    }

    this->setEmpty();
}

Board::~Board() {

    for( uint i = 0; i < this->size; i++ ) {
        delete [] this->board[i];
    }    

    delete [] this->board;
}

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

bool Board::isEmpty( coord c ) {

    //  tests range and emptienes
    if( c.row < this->size && c.col < this->size && this->board[ c.row ][ c.col ] == EMPTY ) { return true; }

    return false;
}

bool Board::isTie( char mark ) {

    for( uint i = 0; i < this->size; i++ ) {
        for( uint j = 0; j < this->size; j++ ) {
            if( this->board[i][j] == EMPTY ) { return false; }
        }
    }

    return true;
}

bool Board::isWin( char mark ) {

    //  tests rows
    for( uint i = 0; i < this->size; i++ ) {
        for( uint j = 0; j < this->size - this->need + 1; j++ ) {

            //  posible win
            if( this->board[i][j] == mark ) {

                bool isWin = true;
                for( uint k = 0; k < this->need; k++ ) {
                    isWin = ( this->board[i][ j + k ] == mark ) ? isWin : false;
                }

                //  is true win
                if( isWin ) { return true; }
            }
        }
    }

    //  tests cols
    for( uint i = 0; i < this->size; i++ ) {
        for( uint j = 0; j < this->size - this->need + 1; j++ ) {

            //  posible win
            if( this->board[j][i] == mark ) {

                bool isWin = true;
                for( uint k = 0; k < this->need; k++ ) {
                    isWin = ( this->board[ j + k ][i] == mark ) ? isWin : false;
                }

                //  is true win
                if( isWin ) { return true; }
            }
        }
    }

    //  test diagonal left-top -> right-bottom
    for( uint i = 0; i < this->size - this->need + 1; i++ ) {
        for( uint j = 0; j < this->size - this->need + 1; j++ ) {
            
            //  posible win
            if( this->board[i][j] == mark ) {

                bool isWin = true;
                for( uint k = 0; k < this->need; k++ ) {
                    isWin = ( this->board[ i + k ][ j + k ] == mark ) ? isWin : false;
                }

                //  is true win
                if( isWin ) { return true; }
            }
        }
    }

    //  test diagonal right-top -> left-bottom
    for( uint i = this->need - 1; i < this->size; i++ ) {
        for( uint j = 0; j < this->size - this->need + 1; j++ ) {

            //  posible win
            if( this->board[i][j] == mark ) {

                bool isWin = true;
                for( uint k = 0; k < this->need; k++ ) {
                    isWin = ( this->board[ i - k ][ j + k ] == mark ) ? isWin : false;
                }

                //  is true win
                if( isWin ) { return true; }
            }
        }
    }

    return false;
}

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

void Board::setSize( uint size ) {

    //  delete prev board
    for( uint i = 0; i < this->size; i++ ) {
        delete [] this->board[i];
    }    

    delete [] this->board;

    //  reset size
    this->size = size;

    //  create new board
    this->board = new char * [ size ];

    for( uint i = 0; i < this->size; i++ ) {
        this->board[i] = new char [ size ];
    }

    this->setEmpty();
}

void Board::setNeed( uint need ) {
    this->need = need;
}

void Board::setEmpty() {

    for( uint i = 0; i < this->size; i++ ) {
        for( uint j = 0; j < this->size; j++ ) {
            this->board[i][j] = EMPTY;
        }
    }
}

void Board::printAll() {

    //  cols print
    for( uint i = 0; i < this->size; i++ ) {

        //  first elem
        if( i == 0 ) { cout << endl << "   "; }

        cout << "| " << i << " ";
    }

    //  loop for rows
    for( uint i = 0; i < this->size; i++ ) {

        //  loop for line breaks
        for( uint j = 0; j < this->size; j++ ) {

            //  first elem
            if( j == 0 ) { cout << endl << "---"; }

            cout << "+---";
        }

        //  loop for rows
        for( uint j = 0; j < this->size; j++ ) {

            //  first elem
            if( j == 0 ) { cout << endl << " " << i << " "; }

            cout << "| " << this->board[ i ][ j ] << " ";
        }

    }

    cout << endl;
}