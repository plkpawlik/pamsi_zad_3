#include <iostream>
#include <stdlib.h> 
#include <cstdio>

using namespace std;

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
//  defines

#define SIZE 3

#define X       'X'
#define O       'O'
#define EMPTY   '?'

#define AI O
#define ME X

#define WIN 10
#define DEF -10
#define TIE 0

#define P_INF  999999
#define N_INF -999999

#define IS_TIE  "Tie!"
#define IS_WIN  "Win!"
#define PENDING "Pending..."

//  global state
string g_message;
string g_result;

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
//  declarations

//  essentials
void printBoard( char * arr );
void setUpBoard( char * arr );

//  state
bool isEmpty( char * arr, int index );
bool isTie( char * arr, char mark );
bool isWin( char * arr, char mark );

//  game
int getShift();
int getBestMove( char * arr );
int minimax( int depth, char * arr, bool isAI );

void insertMark( char * arr, char mark, int index );


/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
//  main

int main() {

    //  init board
    char board[ SIZE *  SIZE ];
    setUpBoard( board );
    printBoard( board );

    /*   *   *   *   *   *   *   *   *   *   */
    //  who starts

    char player_current;
    char player_first = 0;

    while( !player_first ) {

        cout << " Want to be first? ( y / n )" << endl;
        cin >> player_first;

        switch( player_first ) {

            case 'y':
            player_current = ME;
            break;

            case 'Y':
            player_current = ME;
            break;

            case 'n':
            player_current = AI;
            break;

            case 'N':
            player_current = AI;
            break;
            
            default:
            cout << " Invalid option! Try again! " << endl;
            player_first = 0;
            break;
        }
    }

    /*   *   *   *   *   *   *   *   *   *   */

    //  game stop variable
    bool isGamePending = true;

    //  proper game
    while( isGamePending ) {

        int shift;

        //  makes AI
        if( player_current == AI ) {
            shift = getBestMove( board );

        } else {

            //  gets move from player
            shift = getShift();
        }

        insertMark( board, player_current, shift );

        //  prints board
        printBoard( board );

        //  tests for game end
        if( isTie( board, player_current ) ) { isGamePending = false; continue; }
        if( isWin( board, player_current ) ) { isGamePending = false; continue; }

        //  change player
        player_current = ( player_current == X ) ? O : X;
    }
    
    /*   *   *   *   *   *   *   *   *   *   */

    cout << endl;
    cout << " The player -> " << player_current << " <- finishes with a " << g_result << endl;
    cout << endl;
}

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */
//  prototypes

/*   *   *   *   *   *   *   *   *   *   */
//  essentials

void printBoard( char * arr ) {

    system( "clear" );
    
    for( int i = 0; i < SIZE; i++ ) {

        if( i ) {
            for( int j = 0; j < SIZE; j++ ) {
                cout << (( j ) ? "+---" : "---");
            }
        }

        cout << endl;

        for( int j = 0; j < SIZE; j++ ) {
            cout << (( j ) ? "|" : "" ) << ' ' << arr[ i * SIZE + j ] << ' ' ;
        }

        cout << endl;
    }

    cout << endl;
}

void setUpBoard( char * arr ) {

    for( int i = 0; i < SIZE; i++ ) {
        for( int j = 0; j < SIZE; j++ ) {
            arr[ i * SIZE + j ] = EMPTY;
        }
    }

    g_message = "";
    g_result = PENDING;
}

/*   *   *   *   *   *   *   *   *   *   */
//  state

bool isEmpty( char * arr, int index ) {

    if( arr[index] == EMPTY ) { return true; }

    return false;
}

bool isTie( char * arr, char mark ) {

    for( int i = 0; i < SIZE; i++ ) {
        for( int j = 0; j < SIZE; j++ ) {
            if( arr[ i * SIZE + j ] == EMPTY ) { return false; }
        }
    }

    return true;
}

/*
bool isWin( char * arr, char mark ) {

    //  rows
    if( arr[0] == mark && arr[0] == arr[1] && arr[1] == arr[2] ) { return true; }
    if( arr[3] == mark && arr[3] == arr[4] && arr[4] == arr[5] ) { return true; }
    if( arr[6] == mark && arr[6] == arr[7] && arr[7] == arr[8] ) { return true; }

    //  columns
    if( arr[0] == mark && arr[0] == arr[3] && arr[3] == arr[6] ) { return true; }
    if( arr[1] == mark && arr[1] == arr[4] && arr[4] == arr[7] ) { return true; }
    if( arr[2] == mark && arr[2] == arr[5] && arr[5] == arr[8] ) { return true; }

    //  diagonals
    if( arr[0] == mark && arr[0] == arr[4] && arr[4] == arr[8] ) { return true; }
    if( arr[2] == mark && arr[2] == arr[4] && arr[4] == arr[6] ) { return true; }

    return false;
}
*/

bool isWin( char * arr, char mark ) {

    //  tests for rows
    for( int i = 0; i < SIZE; i++ ) {

        //  first elem in a row
        if( arr[ i * SIZE ] != mark ) { continue; }

        //  possible win detected
        bool isWin = true;

        for( int j = 0; j < SIZE; j++ ) {
            isWin = (( arr[ i * SIZE + j ] == mark ) ? isWin : false );
        }

        //  checks for true win
        if( isWin ) { return true; }
    }

    //  tests for column
    for( int i = 0; i < SIZE; i++ ) {

        //  first elem in a column
        if( arr[i] != mark ) { continue; }

        //  possible win detected
        bool isWin = true;

        for( int j = 0; j < SIZE; j++ ) {
            isWin = (( arr[ j * SIZE + i ] == mark ) ? isWin : false );
        }

        //  checks for true win
        if( isWin ) { return true; }
    }

    //  tests diagonal top -> bottom
    if( arr[0] == mark ) {
        
        //  possible win detected
        bool isWin = true;

        for( int i = 0; i < SIZE; i++ ) {
            isWin = (( arr[ i * ( SIZE + 1 ) ] == mark ) ? isWin : false );
        }

        //  checks for true win
        if( isWin ) { return true; }
    }

    //  tests diagonal bottom -> top
    if( arr[ SIZE - 1 ] == mark ) {
        
        //  possible win detected
        bool isWin = true;

        for( int i = 0; i < SIZE; i++ ) {
            isWin = (( arr[ ( i + 1 ) * ( SIZE - 1 ) ] == mark ) ? isWin : false );
        }

        //  checks for true win
        if( isWin ) { return true; }
    }

    return false;
}

/*   *   *   *   *   *   *   *   *   *   */
//  game

int getShift() {

    int row = -1;
    int col = -1;

    //  must be less than size
    while( row < 0 || row > SIZE ) {
        cout << " Specify a row: ";
        cin >> row;
    }

    //  must be less than size
    while( col < 0 || col > SIZE ) {
        cout << " Specify a col: ";
        cin >> col;
    }

    cout << endl;

    return ( row * SIZE + col );
}

int getBestMove( char * arr ) {

    //  initial values
    int bestScore = N_INF;
    int bestShift = -1;

    for( int i = 0; i < ( SIZE * SIZE ); i++ ) {

        //  tests for possible move
        if( isEmpty( arr, i )) {

            //  sets move
            arr[i] = AI;

            int score = minimax( 0, arr, false );
            if( score > bestScore ) {
                bestScore = score;
                bestShift = i;
            }

            //  unsets move
            arr[i] = EMPTY;
        }
    }

    return bestShift;
}

int minimax( int depth, char * arr, bool isAI ) {

    //  terminal states
    if( isWin( arr, ME ) ) { return DEF; }
    if( isWin( arr, AI ) ) { return WIN; }
    if( isTie( arr, AI ) ) { return TIE; }

    //  depth control
    if( depth > 10 ) { return TIE; }

    /*   *   *   *   *   *   *   *   *   *   */
    if( isAI ) {    //  MAXIMIZE
    /*   *   *   *   *   *   *   *   *   *   */

        int bestScore = N_INF;

        for( int i = 0; i < ( SIZE * SIZE ); i++ ) {

            //  tests for possible move
            if( isEmpty( arr, i )) {

                //  sets move
                arr[i] = AI;

                int score = minimax( depth + 1, arr, false );
                if( score > bestScore ) {
                    bestScore = score;
                }

                //  unsets move
                arr[i] = EMPTY;
            }
        }

        return bestScore;

    /*   *   *   *   *   *   *   *   *   *   */
    } else {        //  MINIMIZE
    /*   *   *   *   *   *   *   *   *   *   */
    
        int bestScore = P_INF;

        for( int i = 0; i < ( SIZE * SIZE ); i++ ) {

            //  tests for possible move
            if( isEmpty( arr, i )) {

                //  sets move
                arr[i] = ME;

                int score = minimax( depth + 1, arr, true );
                if( score < bestScore ) {
                    bestScore = score;
                }

                //  unsets move
                arr[i] = EMPTY;
            }
        }

        return bestScore;

    /*   *   *   *   *   *   *   *   *   *   */
    }
}

void insertMark( char * arr, char mark, int index ) {

    if( isEmpty( arr, index ) ) {

        //  inserts mark
        arr[ index ] = mark;

        //  checks for draw or win
        if( isTie( arr, mark ) ) {

            g_message = IS_TIE;
            g_result = IS_TIE;
        }

        if( isWin( arr, mark ) ) {

            g_message = IS_WIN;
            g_result = IS_WIN;
        }


    } else {

        //  index not empty
        cout << endl;
        cout << " Place is not avalible! Select a new one! " << endl;
        cout << endl;

        int shift = -1;

        //  tries to get proper shift
        while( !isEmpty( arr, shift ) ) {
            shift = getShift();
        }

        //  inserts mark
        insertMark( arr, mark, shift );
    }
}