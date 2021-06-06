#include <iostream>
#include <stdlib.h> 
#include <cstdio>
#include <ctime>

using namespace std;

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

#define X       'X'
#define O       'O'
#define EMPTY   ' '

#define WIN     10
#define DEF    -10
#define TIE     0

#define P_INF   0x7FFFFFFF
#define N_INF  -0x7FFFFFFF

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

struct Coordinates  {

    uint row;
    uint col;
};

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

typedef Coordinates coord;